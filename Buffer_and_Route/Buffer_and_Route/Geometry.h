#ifndef GEOMETRY_FUNCTIONS_H
#define GEOMETRY_FUNCTIONS_H

#include "Buffer_and_Route.h"
#include "Buffer.h"

const double ignored_value_d{ 0.000000000000001 };

double latitude1_radian;
double longitude1_radian;
double latitude2_radian;
double longitude2_radian;
double longitude3_radian;
double latitude3_radian;

double cross_product;
double delta_lat;
double delta_lon;
double center_angle_of_circle_arc;
double total_angle_of_the_circular_arc;
double haversine_distance_d;

double haversine_distance(double latitude1, double longitude1, double latitude2, double longitude2);
bool is_vertex_convex(const std::vector<Point>& vertices, int vertex_index);

#endif
