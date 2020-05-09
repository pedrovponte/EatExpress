#include "gtest/gtest.h"
#include "graphviewer.h"
#include "Tests/utils.h"
#include "Tests/Request.h"
#include "Tests/Employee.h"
#include "Tests/Task.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    // User must choose the city and graph is loaded accordingly
    // Preview city graph if user chooses to
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);


    // Pre-process distances using Floyd Warshall
    graph.floydWarshallShortestPath();

    // Generate Random Employees positions
    // TODO

    // Get possible restaurants and let user choose
    Vertex<Coordinates> * restaurant = graph.findVertex(Coordinates(20));
    vector<Vertex<Coordinates>*> restaurants;
    restaurants.push_back(restaurant);

    // Choose user's position or generate random position and request's dimension, date and hour
    Vertex<Coordinates> * delivery_addr = graph.findVertex(Coordinates(42));

    // Build Request
    Request request(0, Date(2020,10,10), Hour(22,0),restaurants,delivery_addr,20);

    // Give the request to an employee
    Employee employee(0,Coordinates(10),40,'c',true);

    Task task(employee,request);

    // Calculate shortest path using FloydWarshall
    task.setFloydWarshallPath(graph);
    vector<Coordinates> path = task.getPath();

    // Show shortest path calculated with FloydWarshall
    viewFloydWarshallShortestPath(graph,path);

    // Calculate shortest path using Dijkstra
    task.setDijkstraPath(graph);
    path.clear();
    path = task.getPath();

    // Show shortest path calculated with Dijkstra
    viewDijkstraShortestPath(graph,path);

    //getchar();
    return RUN_ALL_TESTS();
}