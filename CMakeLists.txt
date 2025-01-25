cmake_minimum_required(VERSION 3.16)

# Set the project name
project(sdl_test)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Add SDL subdirectory
add_subdirectory(SDL)

# Add the executable
add_executable(sdl_test main.c)

# Link SDL3 library
target_link_libraries(sdl_test SDL3::SDL3)