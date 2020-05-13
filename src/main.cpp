#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    simulatePhase3();

    Graph<Coordinates> graph = loadGraph("GridGraphs","20x20Grid", true,false);

    GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    drawGraph(gv,graph);


    return 0;
    return RUN_ALL_TESTS();
}