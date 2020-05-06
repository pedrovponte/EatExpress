#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Tests/Graph.h"
#include "Tests/utils.h"


int main(int argc, char* argv[]) {
    //testing::InitGoogleTest(&argc, argv);

   Graph<Coordinates> g = loadGraph("GridGraphs", "8x8");

    return 0;
    //return RUN_ALL_TESTS();
}