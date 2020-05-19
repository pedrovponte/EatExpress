//
// Created by diana on 09/05/20.
//

#ifndef CAL_T3G4_SINGLETASK_H
#define CAL_T3G4_SINGLETASK_H

#include "Employee.h"
#include "Request.h"
#include "Task.h"

class Request;

class SingleTask : public Task{
    Request request;
    int time;
public:
    SingleTask(Employee *employee, Request request, int id);
    virtual void setFloydWarshallPath(Graph<Coordinates> & graph);
    void setDijkstraPath(Graph<Coordinates> & graph);
    bool isCheckpoint(Coordinates coordinates);
    bool isDeliveryAddress(Coordinates coordinates);
    const Request & getRequest() const;
    int getTime() const;
    bool operator <(const SingleTask & task);
    friend std::ostream &operator<<(std::ostream &os, const SingleTask &task);
};

bool compareTasks(SingleTask * t1, SingleTask * t2);

// Request distribution Phase 2

vector<SingleTask*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

vector<SingleTask*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

// Request distribution Phase 3

min_priority_queue setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests);

void setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);

vector<Employee*> getEligibleEmployees(vector<Employee*> & employees, const Request & request);

bool isDeliverableByVehicle(VehicleType vehicleType, const Request & request);

vector<SingleTask*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees);


// Multiple Restaurants request
vector<Employee*> getEligibleEmployeesMultipleRestaurants(vector<Employee*> & employees, const Request & request);

int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants);

SingleTask * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);


#endif //CAL_T3G4_SINGLETASK_H
