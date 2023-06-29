#include "Buffer_and_Route.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QPolygonF>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <boost/polygon/polygon.hpp>
#include "Buffer.h"
#include "Geometry.h"



//std::vector<BoostPolygon> boost_polygon(const std::vector<std::vector<Point>>& vertices_list) {
//    std::vector<BoostPolygon> boost_polygons;
//
//    for (const auto& vertices : vertices_list) {
//        BoostPolygon boost_polygon;
//        for (const auto& vertex : vertices) {
//            boost::polygon::set_points(boost_polygon, vertex.x, vertex.y);
//        }
//        boost_polygons.push_back(boost_polygon);
//    }
//
//    return boost_polygons;
//}

double haversine_distance(double latitude1, double longitude1, double latitude2, double longitude2) {
    const double earth_radius = 6371000.0;

    latitude1_radian   = latitude1 * M_PI / 180.0;
    longitude1_radian  = longitude1 * M_PI / 180.0;
    latitude2_radian   = latitude2 * M_PI / 180.0;
    longitude2_radian  = longitude2 * M_PI / 180.0;

    delta_lat          = latitude2_radian - latitude1_radian;
    delta_lon          = longitude2_radian - longitude1_radian;

    center_angle_of_circle_arc = std::sin(delta_lat / 2) * std::sin(delta_lat / 2) +
        std::cos(latitude1_radian) * std::cos(latitude2_radian) *
        std::sin(delta_lon / 2) * std::sin(delta_lon / 2);

    total_angle_of_the_circular_arc = 2 * std::atan2(std::sqrt(center_angle_of_circle_arc),
        std::sqrt(1 - center_angle_of_circle_arc));

    distance = earth_radius * total_angle_of_the_circular_arc;
    return distance;
}

bool is_vertex_convex(const std::vector<Point>& vertices, int vertex_index) {

    int size_of_list = vertices.size();
   
    coordinate_x1 = vertices[(vertex_index - 1 + size_of_list) % size_of_list].x;
    coordinate_y1 = vertices[(vertex_index - 1 + size_of_list) % size_of_list].y;
    coordinate_x2 = vertices[vertex_index].x;
    coordinate_y2 = vertices[vertex_index].y;
    coordinate_x3 = vertices[(vertex_index + 1) % size_of_list].x;
    coordinate_y3 = vertices[(vertex_index + 1) % size_of_list].y;

    cross_product = (coordinate_x2 - coordinate_x1) * (coordinate_y3 - coordinate_y2) -
        (coordinate_y2 - coordinate_y1) * (coordinate_x3 - coordinate_x2);

    return cross_product > 0;
}

std::pair<std::vector<std::vector<Point>>, std::vector<Point>> buffered_point(const std::vector<std::vector<Point>>& poly_list, double distance) {
    std::vector<std::vector<Point>> vertices_list;
    std::vector<Point> vertices_list_t;

    for (const auto& poly : poly_list) {
        size_t size_of_list = poly.size();
        std::deque<Point> poly_coord;

        for (size_t index = 0; index < size_of_list; ++index) {
            const Point& current_vertex = poly[index];
            const Point& prev_vertex = poly[(index + size_of_list - 1) % size_of_list];
            const Point& next_vertex = poly[(index + 1) % size_of_list];

            std::vector<Point> control_vertices = { Point(prev_vertex.x, prev_vertex.y),
                                                    Point(current_vertex.x, current_vertex.y),
                                                    Point(next_vertex.x, next_vertex.y) };

            first_second_vertex_distance = haversine_distance(current_vertex.x, current_vertex.y,
                                                              prev_vertex.x, prev_vertex.y);

            second_third_vertex_distance = haversine_distance(current_vertex.x, current_vertex.y,
                                                              next_vertex.x, next_vertex.y);

            third_first_x_dist = next_vertex.x - prev_vertex.x;
            third_first_y_dist = next_vertex.y - prev_vertex.y;

            total_rate = first_second_vertex_distance + second_third_vertex_distance;

            point_of_bisector_x = prev_vertex.x + ((third_first_x_dist / total_rate) * first_second_vertex_distance);
            point_of_bisector_y = prev_vertex.y + ((third_first_y_dist / total_rate) * first_second_vertex_distance);

            if (std::abs(point_of_bisector_x - current_vertex.x) < 1e-12 &&
                std::abs(point_of_bisector_y - current_vertex.y) < 1e-12) {
                new_point_x = current_vertex.x + 0.000000000000001;
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

        vertices_list.push_back(std::vector<Point>(poly_coord.begin(), poly_coord.end()));
    }

    return std::make_pair(vertices_list, vertices_list_t);
}

double calculateScaleFactor(const std::vector<std::vector<Point>>& polygons, int desiredWidth, int desiredHeight)
{
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();

    // Find the maximum x and y coordinates among all polygons
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

    // Calculate the scaling factor based on the desired width and height
    double scaleX = desiredWidth / maxX;
    double scaleY = desiredHeight / maxY;

    // Choose the smaller scaling factor to ensure the polygons fit within the desired size
    double scaleFactor = std::min(scaleX, scaleY);

    return scaleFactor * 25;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // QGraphicsScene oluþturun ve polygonu ekleyin
    QGraphicsScene scene;

    // Define vectors to store coordinate and polygon information
    std::vector<Point> coordinate_list;
    std::vector<std::vector<Point>> polygon_list;

    std::ifstream file("C:/Users/Lenovo/source/repos/Buffer_and_Route/Buffer_and_Route/Coordinates.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<Point> temp_list;
        int polygon_start_index = 2;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> coordinate;

            while (std::getline(ss, item, ',')) {
                coordinate.push_back(item);
            }

            if (std::stof(coordinate[0]) == 0) {
                polygon_list.push_back(temp_list);
                temp_list.clear();
            }
            else {
                double x_coordinate = std::stod(coordinate[0]);
                double y_coordinate = std::stod(coordinate[1]);
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
    std::vector<std::vector<Point>> vertices_list;
    std::vector<Point> vertices_list_t;

    std::tie(vertices_list, vertices_list_t) = buffered_point(polygon_list,2000);

    // Calculate the scaling factor based on the desired width and height
    int desiredWidth = 800;  
    int desiredHeight = 600; 

    for (const auto& polygon : vertices_list) {
        // Create a QPolygonF to store the polygon's points
        QPolygonF qPolygon;

        // Add the points of the polygon to the QPolygonF with scaling
        for (const auto& point : polygon) {
            
            qPolygon << QPointF(point.x * (calculateScaleFactor(vertices_list, desiredWidth, desiredHeight)),
                                point.y * (calculateScaleFactor(vertices_list, desiredWidth, desiredHeight)));
        }

        // Create a QGraphicsPolygonItem and set its polygon
        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem(qPolygon);

        // Add the polygon item to the scene
        scene.addItem(polygonItem);
    }

    // Calculate the scene rectangle based on the scaled polygons
    QRectF sceneRect = scene.itemsBoundingRect();
    scene.setSceneRect(sceneRect);

    // Create a QGraphicsView and use it to display the scene
    QGraphicsView view(&scene);
    view.resize(desiredWidth, desiredHeight);
    view.show();

    return app.exec();
}
