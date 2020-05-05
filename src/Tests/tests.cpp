#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Graph.h"

using namespace std;
using testing::Eq;


/*Graph<int> createTestGraph() {
	Graph<int> myGraph;

	for(int i = 1; i < 8; i++)
		myGraph.addVertex(i);

	myGraph.addBidirectionalEdge(1, 2, 2);
	myGraph.addBidirectionalEdge(1, 4, 7);
	myGraph.addBidirectionalEdge(2, 4, 3);
	myGraph.addBidirectionalEdge(2, 5, 5);
	myGraph.addBidirectionalEdge(3, 1, 2);
	myGraph.addBidirectionalEdge(3, 6, 5);
	myGraph.addBidirectionalEdge(4, 3, 1);
	myGraph.addBidirectionalEdge(4, 5, 1);
	myGraph.addBidirectionalEdge(4, 7, 4);
	myGraph.addBidirectionalEdge(5, 7, 2);
	myGraph.addBidirectionalEdge(6, 4, 3);
	myGraph.addBidirectionalEdge(7, 6, 4);

	return myGraph;
}*/

Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

TEST(CAL_T3G4, test_dijkstra) {
    Graph<int> myGraph = CreateTestGraph();
    cout << "vfdvf\n";
}



