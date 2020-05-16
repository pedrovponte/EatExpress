#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"
#include "Tests/app.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    //simulatePhase3();

    //Graph<Coordinates> g = loadGraph("GridGraphs", "30x30",true, true);
    //getchar();

    chooseMap();
    return 0;
    return RUN_ALL_TESTS();
}