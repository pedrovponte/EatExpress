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
public:
    Task(Employee *employee, Request request);
    void setFloydWarshallPath(Graph<Coordinates> & graph);
    void setDijkstraPath(Graph<Coordinates> & graph);
    const vector<Coordinates> getPath() const;
    bool isCheckpoint(Coordinates coordinates);
    bool isDeliveryAddress(Coordinates coordinates);

    friend std::ostream &operator<<(std::ostream &os, const Task &task);
};

// Request distribution Phase 2

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

vector<Task*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

#endif //CAL_T3G4_TASK_H
