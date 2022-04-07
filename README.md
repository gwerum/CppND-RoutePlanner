# Route Planning Project

This repository contains an OSM map based implementation of a route planer using the [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) in C++. This project was part of the Udacity Nano Degree program for C++. A starter code for this project was given, the focus of this project has been to implement the search algorithm for the route planer (a simplified version of the route planer known from Google maps).

When running the executable one can decide to either provide a OSM file of a map tile or to use the OSM file stored in this repo. One will be asked then to provide the coordinates of a start and end position, the OSM nodes closest to the provided coordinates will be taken and the fastest route will be computed. The following picture shows a possible result of such a request. 

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/gwerum/CppND-RoutePlanner.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:gwerum/CppND-RoutePlanner.git
 --recurse-submodules
```

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
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

