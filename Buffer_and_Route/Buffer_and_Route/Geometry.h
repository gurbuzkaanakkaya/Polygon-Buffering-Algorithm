#ifndef GEOMETRY_FUNCTIONS_H
#define GEOMETRY_FUNCTIONS_H

#include "Buffer_and_Route.h"
#include "Buffer.h"

double coordinate_x1;
double coordinate_y1;
double coordinate_x2;
double coordinate_y2;
double coordinate_x3;
double coordinate_y3;
double cross_product;

double latitude1_radian;
double longitude1_radian;
double latitude2_radian;
double longitude2_radian;
double delta_lat;
double delta_lon;
double center_angle_of_circle_arc;
double total_angle_of_the_circular_arc;
double distance;

double haversine_distance(double latitude1, double longitude1, double latitude2, double longitude2);
bool is_vertex_convex(const std::vector<Point>& vertices, int vertex_index);

#endif
