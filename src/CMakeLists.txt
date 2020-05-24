cmake_minimum_required(VERSION 3.10)
project(CAL_T3G4)

set(CMAKE_CXX_STANDARD 14)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
 link_libraries(ws2_32 wsock32)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

include_directories(lib/graphViewer)

add_executable(CAL_T3G4 main.cpp src/tests.cpp src/Graph.h src/MutablePriorityQueue.h src/Vertex.h src/Edge.h src/utils.cpp
        src/utils.h src/Coordinates.h src/Coordinates.cpp lib/graphViewer/connection.cpp lib/graphViewer/graphviewer.cpp src/Employee.h src/Employee.cpp
        src/Request.cpp src/Request.h src/SingleTask.cpp src/SingleTask.h src/phase_tests/p1_test.cpp src/simulations.cpp src/simulations.h src/phase_tests/p2_test.cpp src/app.cpp src/app.h src/SpecialTask.cpp src/SpecialTask.h src/Task.cpp src/Task.h src/phase_tests/p3_test.cpp)

target_link_libraries(CAL_T3G4 gtest gtest_main)
