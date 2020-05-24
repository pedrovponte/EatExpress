//
// Created by diana on 10/05/20.
//

#include "../eatExpress/Employee.h"
#include "../eatExpress/Request.h"
#include "../eatExpress/SingleTask.h"
#include "../eatExpress/SpecialTask.h"
#include "../graph/Graph.h"
#include <algorithm>

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

    SingleTask task(&employee, request, 0);

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

    SingleTask task(&employee, request, 0);

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
        vector<SingleTask*> tasks = distributeRequestsByCloseness_FloydWarshall(graph, requestsQueue, employees);

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
        vector<SingleTask*> tasks = distributeRequestsByCloseness_Dijkstra(graph, requestsQueue, employees);

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
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "16x16Bike", true);

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    // Add Employees
    vector<Employee*> employees;
    Employee * employee1 = new Employee(0,Coordinates(41),17,CAR,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(265),9,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(95),13,CAR,true);
    employees.push_back(employee3);
    Employee * employee4= new Employee(3,Coordinates(207),6,MOTORCYCLE,true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4,Coordinates(85),8,BIKE,true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5,Coordinates(112),6,FOOT,true);
    employees.push_back(employee6);

    // Add Requests
    min_priority_queue requests;
    requests.push(Request(0, Date(2020,07,10), Hour(1,0),Coordinates(7),Coordinates(260),5));
    requests.push(Request(1, Date(2020,07,10), Hour(7,0),Coordinates(0),Coordinates(95),5));
    requests.push(Request(2, Date(2020,07,10), Hour(2,0),Coordinates(250),Coordinates(169),3));
    requests.push(Request(3, Date(2020,07,10), Hour(8,40),Coordinates(99),Coordinates(214),6));
    requests.push(Request(4, Date(2020,07,10), Hour(6,30),Coordinates(7),Coordinates(65),2));
    requests.push(Request(5, Date(2020,07,10), Hour(4,30),Coordinates(7),Coordinates(105),3));
    requests.push(Request(6, Date(2020,07,10), Hour(3,10),Coordinates(205),Coordinates(234),2));
    requests.push(Request(7, Date(2020,07,10), Hour(5,10),Coordinates(205),Coordinates(145),4));

    vector<SingleTask*> tasks = distributeRequests(graph, reducedGraph, requests, employees);

    for(SingleTask * task : tasks){
        cout << *task << endl;
        viewSinglePath(graph,task->getPath(),task->getVehicleType());
    }

    viewEmployeesPaths(graph,reducedGraph,tasks);

}

// Multiple restaurants request

void simulateMultipleRestaurantsRequest(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "30x30", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "30x30Bike", true);

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    // Add Employees
    vector<Employee*> employees;
    Employee * employee1 = new Employee(0, Coordinates(50), 1, FOOT, true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1, Coordinates(229), 2, BIKE, true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2, Coordinates(69), 2, BIKE, true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3, Coordinates(452), 1, FOOT, true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4, Coordinates(362), 2, BIKE, true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5, Coordinates(146), 2, BIKE, true);
    employees.push_back(employee6);
    Employee * employee7 = new Employee(6, Coordinates(165), 10, CAR, true);
    employees.push_back(employee7);
    Employee * employee8 = new Employee(7, Coordinates(94), 5, MOTORCYCLE, true);
    employees.push_back(employee8);
    Employee * employee9 = new Employee(8, Coordinates(304), 5, MOTORCYCLE, true);
    employees.push_back(employee9);
    Employee * employee10 = new Employee(9, Coordinates(546), 10, CAR, true);
    employees.push_back(employee10);
    Employee * employee11 = new Employee(10, Coordinates(636), 10, CAR, true);
    employees.push_back(employee11);
    Employee * employee12 = new Employee(11, Coordinates(761), 5, MOTORCYCLE, true);
    employees.push_back(employee12);
    Employee * employee13 = new Employee(12, Coordinates(620), 10, CAR, true);
    employees.push_back(employee13);
    Employee * employee14 = new Employee(13, Coordinates(749), 10, CAR, true);
    employees.push_back(employee14);

    vector<Coordinates> checkpoints;
    checkpoints.push_back(Coordinates(673));
    checkpoints.push_back(Coordinates(899));
    checkpoints.push_back(Coordinates(39));

    Request r(0, Date(2020,07,10), Hour(21,0),checkpoints,Coordinates(76),3);

    SingleTask * task = multipleRestaurantsRequest(graph, reducedGraph, employees, r);

    vector<SingleTask*> tasks;
    tasks.push_back(task);
    if(task->getEmployee() != nullptr){
        cout << *task<< endl;
        if (task->getVehicleType() == CAR || task->getVehicleType() == MOTORCYCLE)
            viewEmployeePath(graph,tasks);
        else if(task->getVehicleType() == BIKE || task->getVehicleType() == FOOT)
            viewEmployeePath(reducedGraph,tasks);
    }
    else cout << *task<< endl;

}

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member

void simulateSimultaneousRequests(){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16",true);

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();

    Employee * employee = new Employee(6, Coordinates(165), 15, CAR, true);

    vector<Request> requests;
    requests.push_back(Request(0, Date(2020,07,10), Hour(16,0),Coordinates(7),Coordinates(260),1));
    requests.push_back(Request(1, Date(2020,07,10), Hour(16,0),Coordinates(0),Coordinates(95),2));
    requests.push_back(Request(2, Date(2020,07,10), Hour(16,0),Coordinates(250),Coordinates(88),3));
    requests.push_back(Request(3, Date(2020,07,10), Hour(16,0),Coordinates(7),Coordinates(169),2));

    SpecialTask * task = simultaneousRequests(graph,requests,employee);
    viewSinglePath(graph,task->getPath());
    for(Coordinates c:task->getPath()){
        cout << c << " ";
    }
}