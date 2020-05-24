//
// Created by edurbrito on 19/05/20.
//

#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "../graph/Graph.h"
#include "../utils/utils.h"
#include "../eatExpress/Employee.h"
#include "../eatExpress/Request.h"
#include "../eatExpress/SingleTask.h"


using namespace std;
using testing::Eq;

void connectivityTest(Graph<Coordinates> graph, string info){

    long total = 0;
    int max = 0;

    for (int i = 0; i < graph.getNumVertex(); ++i) {
        int val = graph.dfs(graph.getVertexSet().at(i)->getInfo()).size();
        total += val;

        if (val > max) max = val;
    }

    cout << "Graph " << info << " - " << "Total Vertices: " << graph.getNumVertex() << " DFS mean: " << total / graph.getNumVertex() << " DFS max: " << max << endl;

}

TEST(CAL_T3G4, test_connectivity_ph3){

    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    connectivityTest(graph,"16x16");

    graph = loadGraph("GridGraphs", "16x16Bike", true);

    connectivityTest(graph,"16x16Bike");

    graph = loadGraph("GridGraphs", "16x16Random", true);

    connectivityTest(graph,"16x16Random");

    graph = loadGraph("GridGraphs", "20x20", true);

    connectivityTest(graph,"20x20");

    graph = loadGraph("GridGraphs", "20x20Bike", true);

    connectivityTest(graph,"20x20Bike");

    graph = loadGraph("GridGraphs", "30x30", true);

    connectivityTest(graph,"30x30");

    graph = loadGraph("GridGraphs", "30x30Bike", true);

    connectivityTest(graph,"30x30Bike");

}