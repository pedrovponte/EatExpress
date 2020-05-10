//
// Created by diana on 09/05/20.
//

#include "Task.h"

Task::Task(const Employee &employee, const Request &request) : employee(employee), request(request) {}

void Task::setFloydWarshallPath(Graph<Coordinates> & graph){
    Coordinates orig = employee.getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0]->getInfo();
    Coordinates dest = request.getDeliveryAddr()->getInfo();

    path = graph.getfloydWarshallPath(orig, checkpoint);
    vector<Coordinates> pathToDest = graph.getfloydWarshallPath(checkpoint, dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());

    employee.setCoordinates(path.at(path.size()-1));
}

void Task::setDijkstraPath(Graph<Coordinates> & graph){
    Coordinates orig = employee.getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0]->getInfo();
    Coordinates dest = request.getDeliveryAddr()->getInfo();

    graph.dijkstraShortestPath(orig);
    path = graph.getPathTo(checkpoint);

    graph.dijkstraShortestPath(checkpoint);
    vector<Coordinates> pathToDest = graph.getPathTo(dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());

    employee.setCoordinates(path.at(path.size()-1));
}

const vector<Coordinates> Task::getPath() const{
    return path;
}

std::ostream &operator<<(std::ostream &os, const Task &task) {
    os << task.employee;
    os << task.request;

    cout << "Path: ";

    for(unsigned int i = 0; i < task.path.size(); i++)
        os << task.path[i] << " ";
    os << endl;

    return os;
}

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    graph.floydWarshallShortestPath();

    double ** W = graph.getDistancesMatrix();
    int origIdx, destIdx;
    Employee employee;
    double dist;
    vector<Task*> tasks;

    vector<Employee>::iterator it;
    vector<Employee>::iterator choice;
    // While there are still requests to distribute
    while(!requests.empty()){
        // Get first request in queue
        // Find the Restaurant in the graph
        destIdx = graph.findVertexIdx(requests.front().getCheckpoints()[0]->getInfo());

        employee = Employee(); // Null employee
        dist = INF;

        // Find the nearest employee available (ready = true)
        for(it = employees.begin(); it != employees.end(); it ++){
            // Find employee's location
            origIdx = graph.findVertexIdx(it->getCoordinates());

            // Employee is ready
            if(it->isReady()){
                // Check if the employee is closer to the checkpoint than the previous one
                if(dist > W[origIdx][destIdx]){
                    // Save the employee that is closer to the checkpoint
                    employee = Employee(*it);
                    choice = it;
                    dist = W[origIdx][destIdx];
                }
            }
        }

        // No more employees available
        if(employee.getType() == INVALID){
            break;
        }

        // An employee was found to fulfill the request
        choice->setReady(false); // Make employee unavailable for other requests
        tasks.push_back(new Task(employee,requests.front())); // Create new task for the request
        requests.pop();
    }

    return tasks;
}