#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"
#include "Tests/app.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    //Graph<Coordinates> g = loadGraph("GridGraphs", "4x4",true, true);
    //getchar();

    chooseMap();

    cout << "Press enter to exit!";
    getchar();

    /*simulateMultipleRestaurantsRequest();
    getchar();*/
    return 0;
    return RUN_ALL_TESTS();
}