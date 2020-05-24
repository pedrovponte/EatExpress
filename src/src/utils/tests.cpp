#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <random>
#include <time.h>
#include "../graph/Graph.h"
#include "../utils/utils.h"

using namespace std;
using testing::Eq;

Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(0, 1, 2, 2);
    myGraph.addEdge(1, 1, 4, 7);
    myGraph.addEdge(2, 2, 4, 3);
    myGraph.addEdge(3, 2, 5, 5);
    myGraph.addEdge(4, 3, 1, 2);
    myGraph.addEdge(5, 3, 6, 5);
    myGraph.addEdge(6, 4, 3, 1);
    myGraph.addEdge(7, 4, 5, 1);
    myGraph.addEdge(8, 4, 6, 6);
    myGraph.addEdge(9, 4, 7, 4);
    myGraph.addEdge(10, 5, 7, 2);
    myGraph.addEdge(11, 6, 4, 3);
    myGraph.addEdge(12, 7, 6, 4);

    return myGraph;
}

template <typename T1, typename T2>
basic_ostream<char>& operator<<(basic_ostream<char> & strm, const pair<T1, T2>& kvPair)
{
    strm << "(" << kvPair.first << ", " << kvPair.second << ")";
    return strm;
}

template <class T>
void checkAllPaths(Graph<T> &g, string expected) {
    stringstream ss;
    vector<Vertex<T>* > vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

template <class T>
void checkSinglePath(vector<T> path, string expected) {
    stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

TEST(CAL_T3G4, test_dijkstra) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.dijkstraShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.dijkstraShortestPath(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(myGraph.getPathTo(7), "1 2 4 5 7 ");

    myGraph.dijkstraShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");

    myGraph.dijkstraShortestPath(7);
    checkSinglePath(myGraph.getPathTo(1), "7 6 4 3 1 ");

    Graph<Coordinates> realGraph = loadGraph("GridGraphs", "4x4", true);

    realGraph.dijkstraShortestPath(Coordinates(0));
    checkSinglePath(realGraph.getPathTo(Coordinates(14)), "0 1 6 11 12 13 14 ");

    checkSinglePath(realGraph.getPathTo(Coordinates(21)), "0 5 10 15 20 21 ");
}

TEST(CAL_T3G4, test_floydWarshall) {
    Graph<int> myGraph = CreateTestGraph();
    myGraph.floydWarshallShortestPath();
    checkSinglePath(myGraph.getfloydWarshallPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getfloydWarshallPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getfloydWarshallPath(7, 1), "7 6 4 3 1 ");

    Graph<Coordinates> realGraph = loadGraph("GridGraphs", "4x4", true);

    realGraph.floydWarshallShortestPath();

    checkSinglePath(realGraph.getfloydWarshallPath(Coordinates(0),Coordinates(14)), "0 1 2 3 4 9 14 ");

    checkSinglePath(realGraph.getfloydWarshallPath(Coordinates(0),Coordinates(21)), "0 1 6 11 16 21 ");

    checkSinglePath(realGraph.getfloydWarshallPath(Coordinates(15),Coordinates(24)), "15 16 17 18 19 24 ");
}



