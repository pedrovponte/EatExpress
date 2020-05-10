//
// Created by diana on 09/05/20.
//

#include "Task.h"

Task::Task(Employee * employee, Request request) : employee(employee), request(request) {}

void Task::setFloydWarshallPath(Graph<Coordinates> & graph){
    Coordinates orig = employee->getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0]->getInfo();
    Coordinates dest = request.getDeliveryAddr()->getInfo();

    path = graph.getfloydWarshallPath(orig, checkpoint);
    vector<Coordinates> pathToDest = graph.getfloydWarshallPath(checkpoint, dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());

    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);
}

void Task::setDijkstraPath(Graph<Coordinates> & graph){
    Coordinates orig = employee->getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0]->getInfo();
    Coordinates dest = request.getDeliveryAddr()->getInfo();

    graph.dijkstraShortestPath(orig);
    path = graph.getPathTo(checkpoint);

    graph.dijkstraShortestPath(checkpoint);
    vector<Coordinates> pathToDest = graph.getPathTo(dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());

    employee->setCoordinates(path.at(path.size()-1));
}

const vector<Coordinates> Task::getPath() const{
    return path;
}

std::ostream &operator<<(std::ostream &os, const Task &task) {
    os << *task.employee;
    if(!task.path.empty())
        os << "Initial Employee's Position: " << task.path[0] << endl;

    os << task.request;

    os  <<  "PATH: ";
    for(unsigned int i = 0; i < task.path.size(); i++)
        os << task.path[i] << " ";
    os << endl;

    return os;
}

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    graph.floydWarshallShortestPath();
    double ** W = graph.getDistancesMatrix();
    int origIdx, destIdx;
    double dist;
    vector<Task*> tasks;
    int employeeIdx;

    // While there are still requests to distribute
    while(!requests.empty()){
        // Get first request in queue
        // Find the Restaurant in the graph
        destIdx = graph.findVertexIdx(requests.front().getCheckpoints()[0]->getInfo());

        employeeIdx = -1; // Null employee
        dist = INF;

        // Find the nearest employee available (ready = true)
        for(int i = 0; i < employees.size(); i++){
            // Find employee's location
            origIdx = graph.findVertexIdx(employees[i].getCoordinates());

            // Employee is ready
            if(employees[i].isReady()){
                // Check if the employee is closer to the checkpoint than the previous one
                if(dist > W[origIdx][destIdx]){
                    // Save the employee that is closer to the checkpoint
                    employeeIdx = i;
                    dist = W[origIdx][destIdx];
                }
            }
        }

        // No more employees available
        if(employeeIdx == -1){
            break;
        }

        // An employee was found to fulfill the request
        employees[employeeIdx].setReady(false); // Make employee unavailable for other requests
        tasks.push_back(new Task(&employees[employeeIdx],requests.front())); // Create new task for the request

        requests.pop();
    }

    return tasks;
}