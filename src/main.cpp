#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"
#include "Tests/app.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    chooseMap();

    //Graph<Coordinates> g = loadGraph("GridGraphs", "16x16Bike",true, true);
    cout << "Press enter to exit!";
    getchar();

    return 0;
    return RUN_ALL_TESTS();
}