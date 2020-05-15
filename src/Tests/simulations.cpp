//
// Created by diana on 10/05/20.
//

#include "Employee.h"
#include "Request.h"
#include "Task.h"
#include "Graph.h"
#include "algorithm"

// Phase 1

void simulateFloydWarshallPhase1(){
    // User must choose the city and graph is loaded accordingly
    // Preview city graph if user chooses to
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);

    // Pre-process distances using Floyd Warshall
    graph.floydWarshallShortestPath();

    // Get possible restaurants and let user choose
    Coordinates  restaurant = Coordinates(20);
    vector<Coordinates> restaurants;
    restaurants.push_back(restaurant);

    // Choose user's position or generate random position and request's dimension, date and hour
    Coordinates delivery_addr = Coordinates(42);

    // Build Request
    Request request(0, Date(2020,10,10), Hour(22,0),restaurants,delivery_addr,20);

    // Give the request to an employee
    Employee employee(0,Coordinates(10),40,CAR,true);

    Task task(&employee,request);

    // Calculate shortest path using FloydWarshall
    task.setFloydWarshallPath(graph);
    vector<Coordinates> path = task.getPath();

    // Show shortest path calculated with FloydWarshall
    viewSinglePath(graph,path);
}

void simulateDijkstraPhase1(){
    // User must choose the city and graph is loaded accordingly
    // Preview city graph if user chooses to
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);

    // Get possible restaurants and let user choose
    Coordinates restaurant = Coordinates(20);
    vector<Coordinates> restaurants;
    restaurants.push_back(restaurant);

    // Choose user's position or generate random position and request's dimension, date and hour
    Coordinates delivery_addr = Coordinates(42);

    // Build Request
    Request request(0, Date(2020,10,10), Hour(22,0),restaurants,delivery_addr,20);

    // Give the request to an employee
    Employee employee(0,Coordinates(10),40,CAR,true);

    Task task(&employee,request);

    // Calculate shortest path using Dijkstra
    task.setDijkstraPath(graph);
    vector<Coordinates> path = task.getPath();

    // Show shortest path calculated with Dijkstra
    viewSinglePath(graph,path);
}

// Phase 2

void simulateFloydWarshallPhase2(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();

    // Add Employees
    vector<Employee> employees;
    Employee employee1(0,Coordinates(4),40,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(9),40,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(0),40,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    vector<Request> requests = getRandomRequests(graph,5);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    int requestsRound = 1;

    // No employees to fulfill the requests
    if(employees.empty()) return;

    while(!requestsQueue.empty()){
        cout << "REQUESTS ROUND " << requestsRound << endl;
        vector<Task*> tasks = distributeRequestsByCloseness_FloydWarshall(graph,requestsQueue,employees);

        // Couldn't find any Employees to fulfill the remaining requests
        if(tasks.empty())
            return;

        // Get requests distribution and paths
        for(int i = 0; i < tasks.size(); i++){
            tasks[i]->setFloydWarshallPath(graph);
            cout << *tasks[i] << endl;
        }
        requestsRound++;
    }
}

void simulateDijkstraPhase2(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    // Add Employees
    vector<Employee> employees;
    Employee employee1(0,Coordinates(4),40,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(9),40,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(0),40,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    vector<Request> requests = getRandomRequests(graph,5);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    int requestsRound = 1;

    // No employees to fulfill the requests
    if(employees.empty()) return;

    while(!requestsQueue.empty()){
        cout << "REQUESTS ROUND " << requestsRound << endl;
        vector<Task*> tasks = distributeRequestsByCloseness_Dijkstra(graph,requestsQueue,employees);

        // Couldn't find any Employees to fulfill the remaining requests
        if(tasks.empty())
            return;

        // Get requests distribution and paths
        for(int i = 0; i < tasks.size(); i++){
            tasks[i]->setDijkstraPath(graph);
            cout << *tasks[i] << endl;
            // viewSinglePath(graph,tasks[i]->getPath());
        }
        requestsRound++;
    }
}

// Phase 3

void simulatePhase3(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "20x20", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "20x20Bike", true);

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    // Add Employees
    vector<Employee*> employees;
    Employee * employee1 = new Employee(0,Coordinates(4),40,MOTORCYCLE,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(9),20,FOOT,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(0),60,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    min_priority_queue requests;
    requests.push(Request(0, Date(2020,07,10), Hour(21,0),Coordinates(3),Coordinates(64),40));
    requests.push(Request(1, Date(2020,07,10), Hour(20,0),Coordinates(9),Coordinates(7),20));
    requests.push(Request(2, Date(2020,07,10), Hour(18,0),Coordinates(25),Coordinates(10),12));
    requests.push(Request(3, Date(2020,07,10), Hour(9,40),Coordinates(22),Coordinates(80),60));
    requests.push(Request(4, Date(2020,07,10), Hour(18,30),Coordinates(9),Coordinates(200),10));
    requests.push(Request(5, Date(2020,07,10), Hour(15,30),Coordinates(76),Coordinates(10),30));
    requests.push(Request(6, Date(2020,07,10), Hour(12,10),Coordinates(3),Coordinates(6),5));

    vector<Task*> tasks = distributeRequests(graph,reducedGraph,requests,employees);

    for(Task * task : tasks){
        cout << *task << endl;
        viewSinglePath(graph,task->getPath(),task->getVehicleType());
    }

    viewEmployeesPaths(graph,reducedGraph,tasks);

}

