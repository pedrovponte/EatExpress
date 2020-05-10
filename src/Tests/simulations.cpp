//
// Created by diana on 10/05/20.
//

#include "simulations.h"
#include "Employee.h"
#include "Request.h"
#include "Task.h"
#include "Graph.h"


void simulateFloydWarshallPhase1(){
    // User must choose the city and graph is loaded accordingly
    // Preview city graph if user chooses to
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);

    // Pre-process distances using Floyd Warshall
    graph.floydWarshallShortestPath();

    // Get possible restaurants and let user choose
    Vertex<Coordinates> * restaurant = graph.findVertex(Coordinates(20));
    vector<Vertex<Coordinates>*> restaurants;
    restaurants.push_back(restaurant);

    // Choose user's position or generate random position and request's dimension, date and hour
    Vertex<Coordinates> * delivery_addr = graph.findVertex(Coordinates(42));

    // Build Request
    Request request(0, Date(2020,10,10), Hour(22,0),restaurants,delivery_addr,20);

    // Give the request to an employee
    Employee employee(0,Coordinates(10),40,CAR,true);

    Task task(&employee,request);

    // Calculate shortest path using FloydWarshall
    task.setFloydWarshallPath(graph);
    vector<Coordinates> path = task.getPath();

    // Show shortest path calculated with FloydWarshall
    viewFloydWarshallShortestPath(graph,path);
}

void simulateDijkstraPhase1(){
    // User must choose the city and graph is loaded accordingly
    // Preview city graph if user chooses to
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);

    // Get possible restaurants and let user choose
    Vertex<Coordinates> * restaurant = graph.findVertex(Coordinates(20));
    vector<Vertex<Coordinates>*> restaurants;
    restaurants.push_back(restaurant);

    // Choose user's position or generate random position and request's dimension, date and hour
    Vertex<Coordinates> * delivery_addr = graph.findVertex(Coordinates(42));

    // Build Request
    Request request(0, Date(2020,10,10), Hour(22,0),restaurants,delivery_addr,20);

    // Give the request to an employee
    Employee employee(0,Coordinates(10),40,CAR,true);

    Task task(&employee,request);

    // Calculate shortest path using Dijkstra
    task.setDijkstraPath(graph);
    vector<Coordinates> path = task.getPath();

    // Show shortest path calculated with Dijkstra
    viewDijkstraShortestPath(graph,path);
}

void simulateFloydWarshallPhase2(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    vector<Employee> employees;
    Employee employee1(0,Coordinates(4),40,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(9),40,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(0),40,CAR,true);
    employees.push_back(employee3);
    /*Employee employee4(3,Coordinates(8),40,CAR,true);
    employees.push_back(employee4);*/

    vector<Request> requests = getRandomRequests(graph,5);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    vector<Task*> tasks = distributeRequestsByCloseness_FloydWarshall(graph,requestsQueue,employees);

    for(int i = 0; i < tasks.size(); i++){
        tasks[i]->setFloydWarshallPath(graph);

        cout << *tasks[i] << endl;

        //viewFloydWarshallShortestPath(graph,tasks[i]->getPath());
    }
}