cmake_minimum_required(VERSION 3.21)
project(cpp-project CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to be used")

# output directory set to project/output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $PROJECT_SOURCE_DIR/output)
add_subdirectory(src)
