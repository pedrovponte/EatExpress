#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"
#include "Tests/app.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    chooseMap();
    //Graph<Coordinates> graph = loadGraph("PortugalMaps", "Espinho", true, true);
     // simulateSimultaneousRequests();

    cout << "\tPress ENTER to exit!";
    getchar();
    return 0;
    //return RUN_ALL_TESTS();
}