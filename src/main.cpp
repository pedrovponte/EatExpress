#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    //simulatePhase3();

    Graph<Coordinates> g = loadGraph("GridGraphs", "16x16",true, true);
    getchar();
    return 0;
    return RUN_ALL_TESTS();
}