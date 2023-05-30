# Route Planner

This is a simple project in C++ to implement a route planner for a vehicle (or pedestrian, etc.).
Simple mostly because the starter code was robust, I changed `main.cpp` and implemented modularized
code for A* search using Euclidean distance from point to end point as the h(euristic) value.

The program takes in an XML file of data (named as an OSM file) represented as nodes, ways, and relations.
Nodes are points with x and y coordinates and metadata, ways are collections of points representing a path, 
and relations are groups of ways (e.g. multiple paths representing a freeway course). 

Specifically, I:

- Used the extraction operator `>>` to save user input in [`main.cpp`](). Used implicit conversion from int to float 
during variable reassignment of start and end coordinates. Using floats means the user is forced to write the
number as a float e.g. `10f` or `10.0`.
- Filled out methods in [`route_planner.cpp`](), with helpful comments on potential errors and additional information.
All methods filled out are marked by a TODO. :~)


<img src="map.png" width="600" height="450" />


## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

  IO2D had issues for me during a Windows installation, WSL 2 is recommended to use the Linux version.

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, the project can be run with:

```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`,  unit tests can be run as follows:
```
./test
```

