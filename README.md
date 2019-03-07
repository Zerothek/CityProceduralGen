# CityProceduralGen
Procedurally Generated City in OpenGL

The program will generate a grid of Height x Width dimmenssion based
on the maxTunnels and maxLenght parameters, where each cell of the
grid will be populated by either a road or a building.
maxLength: the greatest length of each tunnel the algorithm will choose
before making a horizontal or vertical turn.
maxTunnels: the greatest number of turns the algorithm can take while 
making the map.
You can tweak these 4 variables however you want to get the desired city.
You can move around the city by holding down the right mouse button
and by using the WASD keys, and the Q and E buttons for moving on the 
vertical axis.

The buildings have 2 or three floors and are consisted of blocks that are
in the shape of a triangular prism, a hexagonal prism or a cube.

In order to start the program you have to open Framework_EGC.sln(which is located
in the Visual Studio folder) and compile the program.The sources are located
in the Source/BrickBreaker folder.
