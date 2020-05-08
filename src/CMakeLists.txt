cmake_minimum_required(VERSION 3.10)
project(CAL_T3G4)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32 wsock32)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

include_directories(lib/graphViewer)

add_executable(CAL_T3G4 main.cpp Tests/tests.cpp Tests/Graph.h Tests/MutablePriorityQueue.h Tests/Vertex.h Tests/Edge.h Tests/utils.cpp
        Tests/utils.h Tests/Coordinates.h Tests/Coordinates.cpp lib/graphViewer/connection.cpp lib/graphViewer/graphviewer.cpp Tests/Employee.h Tests/Employee.cpp
        Tests/Request.cpp Tests/Request.h)

target_link_libraries(CAL_T3G4 gtest gtest_main)
