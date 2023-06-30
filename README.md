![b2564d6c-8b85-4304-a743-00e923670a1a](https://github.com/gurbuzkaanakkaya/Polygon-Buffering-Algorithm/assets/103320421/4ec3f70f-4575-44c7-8269-a0eea8b39057)


     A polygon buffered based on the Haversine distance


     Creating an instance of the QGraphicsScene class:
With the line QGraphicsScene scene;, an instance of the QGraphicsScene class is created. This object represents a scene that contains graphics items and graphical elements. The scene variable provides control over this scene.

Defining empty vectors for the coordinate list and polygon list:
The lines vector<Point> coordinate_list; and vector<vector<Point>> polygon_list; define empty vectors. coordinate_list is the vector that holds the coordinates, and polygon_list is the vector that holds the polygons.

Opening and reading the contents of the Coordinates.txt file:
The line ifstream file("Coordinates.txt"); opens the "Coordinates.txt" file and associates it with an ifstream object named file. This object is used to read the contents of the file.

Adding coordinates and polygons to the appropriate vectors:
Inside the while (getline(file, line)) { ... } code block, the file is read line by line, and the coordinates and polygons are added to the appropriate vectors. Each line is read using the getline function and stored in the line variable. Then, the line is split into segments using stringstream and added to the coordinate vector. If the coordinates are equal to 0, it indicates the end of a polygon, and the temporary coordinate list (temp_list) is added to the polygon_list vector. Otherwise, the coordinates are added to the coordinate_list vector.

buffered_point function: This function calculates buffered polygons based on the given polygon list using a specified distance value. The buffered polygons are stored in the vectors named vertices_list and vertices_list_t. The poly_list parameter represents the original polygon list. The function uses the haversine distance calculation function (haversine_distance) and the function to check if vertices are convex (is_vertex_convex) for the buffering process.

calculateScaleFactor function: This function calculates the scale factor based on the given polygon list and desired width and height values. The polygons parameter represents the polygon list. The function finds the maximum x and y coordinates for each polygon and calculates an appropriate scale factor by comparing these values with the desired width and height.

The buffered polygons are converted into QGraphicsPolygonItem objects and added to the QGraphicsScene.

An object of the QRectF class is created to define the boundaries of the scene and set the scene's bounding rectangle using the items within it.

An object of the QGraphicsView class is created and its size is set to display the scene properly.
