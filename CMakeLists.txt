cmake_minimum_required(VERSION 3.15)
project(cppcoverage)

set(CMAKE_CXX_STANDARD 14)

# add subprojects
add_subdirectory(src)
add_subdirectory(libs)

# note: this adds a BUILD_TESTING which defaults to ON
include(CTest)
include(${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake)

# if build testing is on, add tests subdir (where CMakeLists.txt is)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()