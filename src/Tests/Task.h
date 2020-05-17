//
// Created by diana on 09/05/20.
//

#ifndef CAL_T3G4_TASK_H
#define CAL_T3G4_TASK_H

#include "Employee.h"
#include "Request.h"

class Request;

class Task {
    Employee * employee;
    Request request;
    vector<Coordinates> path;
    double totalDistance;
public:
    Task(Employee *employee, Request request);
    void setFloydWarshallPath(Graph<Coordinates> & graph);
    void setDijkstraPath(Graph<Coordinates> & graph);
    const vector<Coordinates> getPath() const;
    bool isCheckpoint(Coordinates coordinates);
    bool isDeliveryAddress(Coordinates coordinates);
    VehicleType getVehicleType() const;
    const Request & getRequest() const;
    Employee *getEmployee() const;
    bool operator <(const Task & task);
    friend std::ostream &operator<<(std::ostream &os, const Task &task);
};

bool compareTasks(Task * t1, Task * t2);

// Request distribution Phase 2

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

vector<Task*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

// Request distribution Phase 3

min_priority_queue setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests);

void setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);

vector<Employee*> getEligibleEmployees(vector<Employee*> & employees, const Request & request);

bool isDeliverableByVehicle(VehicleType vehicleType, const Request & request);

bool compareEmployees(Employee * e1, Employee * e2);

vector<Task*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees);


// Multiple Restaurants request
vector<Employee*> getEligibleEmployeesMultipleRestaurants(vector<Employee*> & employees, const Request & request);

int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants);

Task * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);

#endif //CAL_T3G4_TASK_H
