# SDL3 test project.

## Setup

### Dependencies
#### SDL3
Project uses SDL3 and is included in the project via a git submodule and resides in ```./SDL``` from which it is included via CMake

### CMake setup
Before doing your first build, you might want to modify the project name and the name of the output executable, also **remember to update the name in the Link step!!**
```cmake
cmake_minimum_required(VERSION 3.16)

# Set the project name
project(sdl_test) # <-- Define project name here

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Add SDL subdirectory
add_subdirectory(SDL)

# Add the executable
add_executable(sdl_test main.c) # <-- Define executable name here

# Link SDL3 library
target_link_libraries(sdl_test SDL3::SDL3) # <-- Remember to update the name reference for the linkins as well!
```
### Build
```sh
cmake -S . -B build # Set source and build dir respectively
cmake --build build # Run the build
```