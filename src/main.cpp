#include <fstream>
#include "Tests/utils.h"
#include "gtest/gtest.h"
#include "Tests/simulations.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    Graph<Coordinates> graph = loadGraph("GridGraphs","30x30Bike", true,false);


    cleanGraph(&graph); // SEE HERE HOW I CLEANED SOME VERTEXES ONLY TO SHOW


    GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    drawGraph(gv,graph);

    graph = loadGraph("GridGraphs","30x30", true,false);


    cleanGraph(&graph);  // SEE HERE HOW I CLEANED SOME VERTEXES ONLY TO SHOW 


    gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    drawGraph(gv,graph);

    return 0;

    return RUN_ALL_TESTS();
}