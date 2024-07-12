cmake_minimum_required(VERSION 3.16..3.24)
project(Assignment_2 VERSION 0.0.1
                    DESCRIPTION "Assignment 2"
                    LANGUAGES CXX)

# Update the submodules here
include(src/cmake/UpdateSubmodule.cmake)
# Enable testing for this project
include(CTest)
# Add subdirectories with code
add_subdirectory(src)
add_subdirectory(src/external)
add_subdirectory(src/test)