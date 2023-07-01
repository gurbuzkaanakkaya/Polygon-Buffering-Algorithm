
# Polygon Buffering Algorithm: Generating Buffer Points

The project reads data from a file called "Coordinates.txt" and processes coordinates and polygons stored within it. It uses vectors to store the coordinates and polygons. The project includes functions for buffering polygons based on a specified distance and calculating the scale factor based on desired dimensions. The QGraphicsScene and QGraphicsPolygonItem classes are utilized to visually represent the buffered polygons within a scene. The QRectF class defines the scene boundaries, and the QGraphicsView class displays the scene properly.



## Authors 

- [@gurbuzkaanakkaya](https://www.github.com/gurbuzkaanakkaya) 


  

  



  

    


  


  
## Features

- Data File Reading:
    The project utilizes a data file named "Coordinates.txt".
    The file is a text file that stores coordinates and polygons.
    The file is read using ifstream and its contents are processed. 
- Coordinate and Polygon Lists:
    The project utilizes vectors to store coordinates and polygons.
    The "coordinate_list" vector is used for storing coordinates.
    The "polygon_list" vector is used for storing polygons.
- Buffering Operation:
    The "buffered_point" function calculates buffered polygons on the given polygon list using a specified distance value.
    Buffered polygons are stored in the "vertices_list" and "vertices_list_t" vectors.
    The function utilizes the Haversine distance calculation function ("haversine_distance") and a function to check the convexity of vertices ("is_vertex_convex").
- Calculation of Scale Factor:
    The "calculateScaleFactor" function calculates the scale factor based on the given polygon list and desired width and height values.
    The function finds the maximum x and y coordinates for each polygon and calculates an appropriate scale factor by comparing these values with the desired width     and height.
- Usage of QGraphicsScene and QGraphicsPolygonItem:
    The QGraphicsScene class represents scenes and contains graphical objects.
    Buffered polygons are converted into QGraphicsPolygonItem objects and added to the QGraphicsScene.
    This way, polygons are visually represented within the scene.
- Usage of QRectF and QGraphicsView:
    The QRectF class defines the boundaries of the scene and sets the bounding rectangle of the scene using the items within it.
    The QGraphicsView class is used to display the scene and its size is adjusted to ensure proper visualization of the scene.
  

  
## Output

![b2564d6c-8b85-4304-a743-00e923670a1a](https://github.com/gurbuzkaanakkaya/Polygon-Buffering-Algorithm/assets/103320421/8f239647-180b-43d0-ab02-5b5fc6cef9ac)


  

  

  
