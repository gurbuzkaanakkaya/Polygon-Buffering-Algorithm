#include "Buffer_and_Route.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QPolygonF>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include "Buffer.h"
#include "Geometry.h"

using namespace std;

double haversine_distance(double latitude1, double longitude1, double latitude2, double longitude2) {
    const double earth_radius = 6371000.0;

    latitude1_radian                = latitude1             * M_PI / 180.0;
    longitude1_radian               = longitude1            * M_PI / 180.0;
    latitude2_radian                = latitude2             * M_PI / 180.0;
    longitude2_radian               = longitude2            * M_PI / 180.0;

    delta_lat                       = latitude2_radian      - latitude1_radian;
    delta_lon                       = longitude2_radian     - longitude1_radian;

    center_angle_of_circle_arc      = sin(delta_lat / 2)    * sin(delta_lat / 2)    +
                                      cos(latitude1_radian) * cos(latitude2_radian) *
                                      sin(delta_lon / 2)    * sin(delta_lon / 2);

    total_angle_of_the_circular_arc = 2                     * atan2(sqrt(center_angle_of_circle_arc),
                                                              sqrt(1 - center_angle_of_circle_arc));

    haversine_distance_d            = earth_radius          * total_angle_of_the_circular_arc;

    return haversine_distance_d;
}

bool is_vertex_convex(const vector<Point>& vertices, int vertex_index) {

    int size_of_list  = vertices.size();
   
    latitude1_radian  = vertices[(vertex_index - 1 + size_of_list) % size_of_list].x;
    longitude1_radian = vertices[(vertex_index - 1 + size_of_list) % size_of_list].y;
    latitude2_radian  = vertices[vertex_index].x;
    longitude2_radian = vertices[vertex_index].y;
    latitude3_radian  = vertices[(vertex_index + 1) % size_of_list].x;
    longitude3_radian = vertices[(vertex_index + 1) % size_of_list].y;

    cross_product     = (latitude2_radian  - latitude1_radian)  * (longitude3_radian - longitude2_radian) -
                        (longitude2_radian - longitude1_radian) * (latitude3_radian  - latitude2_radian);

    return cross_product > 0;
}

pair<vector<vector<Point>>, vector<Point>> buffered_point(const vector<vector<Point>>& poly_list, double distance) {
    vector<vector<Point>> vertices_list;
    vector<Point> vertices_list_t;

    for (const auto& poly : poly_list) {
        size_t size_of_list = poly.size();
        deque<Point> poly_coord;

        for (size_t index = 0; index < size_of_list; ++index) {

            const Point& current_vertex    = poly[index];
            const Point& prev_vertex       = poly[(index + size_of_list - 1) % size_of_list];
            const Point& next_vertex       = poly[(index + 1) % size_of_list];

            vector<Point> control_vertices = {Point(prev_vertex.x,    prev_vertex.y),
                                              Point(current_vertex.x, current_vertex.y),
                                              Point(next_vertex.x,    next_vertex.y)};

            first_second_vertex_distance   = haversine_distance(current_vertex.x, current_vertex.y,
                                                                prev_vertex.x,    prev_vertex.y);

            second_third_vertex_distance   = haversine_distance(current_vertex.x, current_vertex.y,
                                                                next_vertex.x,    next_vertex.y);

            third_first_x_dist             = next_vertex.x                - prev_vertex.x;
            third_first_y_dist             = next_vertex.y                - prev_vertex.y;

            total_rate                     = first_second_vertex_distance + second_third_vertex_distance;

            point_of_bisector_x            = prev_vertex.x                + ((third_first_x_dist / total_rate) * first_second_vertex_distance);
            point_of_bisector_y            = prev_vertex.y                + ((third_first_y_dist / total_rate) * first_second_vertex_distance);

            if (abs(point_of_bisector_x - current_vertex.x) < 1e-12 &&
                abs(point_of_bisector_y - current_vertex.y) < 1e-12) {

                new_point_x         = current_vertex.x + ignored_value_d;
                Point new_point(new_point_x, current_vertex.y);
                control_vertices[1] = new_point;
            }

            bisector_distance_vertex = haversine_distance(current_vertex.x, current_vertex.y,
                                                          point_of_bisector_x, point_of_bisector_y);


            if (!is_vertex_convex(control_vertices, 1)) {
                new_point_x = current_vertex.x + (current_vertex.x - point_of_bisector_x) * distance / bisector_distance_vertex;
                new_point_y = current_vertex.y + (current_vertex.y - point_of_bisector_y) * distance / bisector_distance_vertex;
            }
            else {
                new_point_x = current_vertex.x - (current_vertex.x - point_of_bisector_x) * distance / bisector_distance_vertex;
                new_point_y = current_vertex.y - (current_vertex.y - point_of_bisector_y) * distance / bisector_distance_vertex;
            }

            Point new_point(new_point_x, new_point_y);
            poly_coord.push_back(new_point);
            vertices_list_t.push_back(new_point);
        }

        vertices_list.push_back(vector<Point>(poly_coord.begin(), poly_coord.end()));
    }

    return make_pair(vertices_list, vertices_list_t);
}

double calculateScaleFactor(const vector<vector<Point>>& polygons, int desiredWidth, int desiredHeight)
{
    double maxX = numeric_limits<double>::min();
    double maxY = numeric_limits<double>::min();

    for (const auto& polygon : polygons) {
        for (const auto& point : polygon) {
            if (point.x > maxX) {
                maxX = point.x;
            }
            if (point.y > maxY) {
                maxY = point.y;
            }
        }
    }

    double scaleX      = desiredWidth  / maxX;
    double scaleY      = desiredHeight / maxY;

    double scaleFactor = min(scaleX, scaleY);

    return scaleFactor * 25;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;

    vector<Point> coordinate_list;
    vector<vector<Point>> polygon_list;

    ifstream file("Coordinates.txt");
    if (file.is_open()) {
        string line;
        vector<Point> temp_list;
        int polygon_start_index = 2;

        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> coordinate;

            while (getline(ss, item, ',')) {
                coordinate.push_back(item);
            }
            

            if (stof(coordinate[0]) == 0) {
                polygon_list.push_back(temp_list);
                temp_list.clear();
            }
            else {
                double x_coordinate = stod(coordinate[0]);
                double y_coordinate = stod(coordinate[1]);
                Point point(x_coordinate, y_coordinate);
                coordinate_list.push_back(point);
                if (polygon_start_index > 0) {
                    polygon_start_index--;
                }
                else {
                    temp_list.push_back(point);
                }
            }
        }
    }
    vector<vector<Point>> vertices_list;
    vector<Point> vertices_list_t;

    tie(vertices_list, vertices_list_t) = buffered_point(polygon_list);

    int desiredWidth = 800;  
    int desiredHeight = 600; 

    for (const auto& polygon : vertices_list) {
        QPolygonF qPolygon;

        for (const auto& point : polygon) {
            
            qPolygon << QPointF(point.x * (calculateScaleFactor(vertices_list, desiredWidth, desiredHeight)),
                                point.y * (calculateScaleFactor(vertices_list, desiredWidth, desiredHeight)));
        }

        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem(qPolygon);

        scene.addItem(polygonItem);
    }

    QRectF sceneRect = scene.itemsBoundingRect();
    scene.setSceneRect(sceneRect);

    QGraphicsView view(&scene);
    view.resize(desiredWidth, desiredHeight);
    view.show();

    return app.exec();
}
