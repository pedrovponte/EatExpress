#include "gtest/gtest.h"
#include "graphviewer.h"
#include "Tests/utils.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    /*GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    // Show initial graph
    //viewFileGraph(gv, "GridGraphs", "4x4", true);

    // Show final shortest path
    Graph<Coordinates> g = loadGraph("GridGraphs", "4x4", true);

    viewDijkstraShortestPath(gv, g, Coordinates(0),Coordinates(14));

    //viewFloydWarshallShortestPath(gv,g,Coordinates(0),Coordinates(14));

    gv->rearrange();

    getchar();*/
    return RUN_ALL_TESTS();
}