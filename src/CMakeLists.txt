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

add_executable(CAL_T3G4 main.cpp src/utils/tests.cpp src/graph/Graph.h src/graph/MutablePriorityQueue.h src/graph/Vertex.h src/graph/Edge.h src/utils/utils.cpp
        src/utils/utils.h src/eatExpress/Coordinates.h src/eatExpress/Coordinates.cpp lib/graphViewer/connection.cpp lib/graphViewer/graphviewer.cpp src/eatExpress/Employee.h src/eatExpress/Employee.cpp
        src/eatExpress/Request.cpp src/eatExpress/Request.h src/eatExpress/SingleTask.cpp src/eatExpress/SingleTask.h src/phase_tests/p1_test.cpp src/simulations/simulations.cpp src/simulations/simulations.h src/phase_tests/p2_test.cpp src/app/app.cpp src/app/app.h src/eatExpress/SpecialTask.cpp src/eatExpress/SpecialTask.h src/eatExpress/Task.cpp src/eatExpress/Task.h src/phase_tests/p3_test.cpp)

target_link_libraries(CAL_T3G4 gtest gtest_main)
