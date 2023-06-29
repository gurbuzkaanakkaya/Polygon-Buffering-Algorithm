#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <utility>
#include <cmath>

struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};


double first_second_vertex_distance;
double second_third_vertex_distance;
double third_first_x_dist;
double third_first_y_dist;
double total_rate;
double point_of_bisector_x;
double point_of_bisector_y;
double bisector_distance_vertex;
double new_point_x;
double new_point_y;

std::pair<std::vector<std::vector<Point>>, std::vector<Point>> buffered_point(const std::vector<std::vector<Point>>& poly_list, double distance = 100.0);

#endif
