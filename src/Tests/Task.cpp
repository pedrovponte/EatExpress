//
// Created by diana on 09/05/20.
//

#include "Task.h"

// Task class

Task::Task(Employee * employee, Request request) : employee(employee), request(request) {}

void Task::setFloydWarshallPath(Graph<Coordinates> & graph){
    Coordinates orig = employee->getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0];
    Coordinates dest = request.getDeliveryAddr();

    path = graph.getfloydWarshallPath(orig, checkpoint);
    vector<Coordinates> pathToDest = graph.getfloydWarshallPath(checkpoint, dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());
    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);
}

void Task::setDijkstraPath(Graph<Coordinates> & graph){
    Coordinates orig = employee->getCoordinates();
    Coordinates checkpoint = request.getCheckpoints()[0];
    Coordinates dest = request.getDeliveryAddr();

    graph.dijkstraShortestPath(orig);
    path = graph.getPathTo(checkpoint);

    graph.dijkstraShortestPath(checkpoint);
    vector<Coordinates> pathToDest = graph.getPathTo(dest);
    path.insert(path.end(),pathToDest.begin()+1, pathToDest.end());

    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);
}

const vector<Coordinates> Task::getPath() const{
    return path;
}

bool Task::isCheckpoint(Coordinates coordinates){
    vector<Coordinates> checkpoints = request.getCheckpoints();
    for(int i = 0; i< checkpoints.size(); i++){
        if(checkpoints[i] == coordinates)
            return true;
    }
    return false;
}

bool Task::isDeliveryAddress(Coordinates coordinates){
    return request.getDeliveryAddr() == coordinates;
}

VehicleType Task::getVehicleType() const{
    if(employee == nullptr)
        return INVALID;
    return employee->getType();
}

std::ostream &operator<<(std::ostream &os, const Task &task) {
    if(task.employee == nullptr){
        os << task.request;
        os << "Request couldn't be completed!"<< endl;
        return os;
    }

    os << task.request;

    os << *task.employee;
    if(!task.path.empty())
        os << "Initial Employee's Position: " << task.path[0] << endl;

    os  <<  "PATH: ";
    for(unsigned int i = 0; i < task.path.size(); i++)
        os << task.path[i] << " ";
    os << endl;

    return os;
}

bool  Task::operator <(const Task & task){
    if(this->getVehicleType() != INVALID && task.getVehicleType() != INVALID){
        if(employee->getId() == task.employee->getId()){
            return request < task.getRequest();
        }
        return employee->getId() < task.employee->getId();
    }

    return(this->getVehicleType() != INVALID && task.getVehicleType() == INVALID);
}

const Request & Task::getRequest() const {
    return request;
}

Employee *Task::getEmployee() const {
    return employee;
}

bool compareTasks(Task * t1, Task * t2){
    return *t1 < *t2;
}

// Request distribution Phase 2

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    int origIdx, destIdx;
    double dist;
    vector<Task*> tasks;
    int employeeIdx;

    // While there are still requests to distribute
    while(!requests.empty()){
        // Get first request in queue
        // Find the Restaurant in the graph
        destIdx = graph.findVertexIdx(requests.front().getCheckpoints()[0]);

        employeeIdx = -1; // Null employee
        dist = INF;

        // Find the nearest employee available (ready = true)
        for(int i = 0; i < employees.size(); i++){
            // Find employee's location
            origIdx = graph.findVertexIdx(employees[i].getCoordinates());

            // Employee is ready
            if(employees[i].isReady()){
                // Check if the employee is closer to the checkpoint than the previous one
                if(dist > graph.getDist(origIdx,destIdx)){
                    // Save the employee that is closer to the checkpoint
                    employeeIdx = i;
                    dist = graph.getDist(origIdx,destIdx);
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

vector<Task*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    vector<Task*> tasks;
    int employeeIdx;
    double dist;

    while(!requests.empty()){
        employeeIdx = -1; // Null employee
        dist = INF;

        // Find the nearest employee available (ready = true)
        for(int i = 0; i < employees.size(); i++){
            // Get first request in queue - find the Restaurant in the graph
            Coordinates checkpoint = requests.front().getCheckpoints()[0];
            Vertex<Coordinates> * v = graph.findVertex(checkpoint);

            // Employee is ready
            if(employees[i].isReady()){

                // Calculate distances
                graph.dijkstraShortestPath(employees[i].getCoordinates());

                // Check if the employee is closer to the checkpoint than the previous one
                if(dist > v->getDist()){
                    // Save the employee that is closer to the checkpoint
                    employeeIdx = i;
                    dist = v->getDist();
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


// Request distribution Phase 3

min_priority_queue setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests){

    int origIdx1, origIdx2, destIdx1, destIdx2;
    min_priority_queue requestsQueue;

    while(!requests.empty()){
        Request request = requests.top();
        requests.pop();

        origIdx1 = graph.findVertexIdx(request.getCheckpoints()[0]);
        destIdx1 = graph.findVertexIdx(request.getDeliveryAddr());

        origIdx2 = reducedGraph.findVertexIdx(request.getCheckpoints()[0]);
        destIdx2 = reducedGraph.findVertexIdx(request.getDeliveryAddr());

        if(origIdx1 != -1 && destIdx1 != -1 && graph.getDist(origIdx1,destIdx1) != INF)
            request.setDeliverableByCar(true);

        if(origIdx2 != -1 && destIdx2 != -1 && reducedGraph.getDist(origIdx2,destIdx2) != INF)
            request.setDeliverableByFoot(true);

        requestsQueue.push(request);
    }

    return requestsQueue;
}

void setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, const Request & request){
    int origIdx;
    int checkpointIdx1 = graph.findVertexIdx(request.getCheckpoints()[0]);
    int checkpointIdx2 = reducedGraph.findVertexIdx(request.getCheckpoints()[0]);

    for(Employee * e : employees){

        if(e->getType() == CAR || e->getType() == MOTORCYCLE){
            origIdx =  graph.findVertexIdx(e->getCoordinates());
            e->setDist(graph.getDist(origIdx, checkpointIdx1));
        }
        else if(e->getType() == BIKE || e->getType() == FOOT){
            origIdx =  reducedGraph.findVertexIdx(e->getCoordinates());
            e->setDist(reducedGraph.getDist(origIdx, checkpointIdx2));
        }
    }
}

vector<Employee*> getEligibleEmployees(vector<Employee*> & employees, const Request & request){
    vector<Employee*> eligibleEmployees;

    for(Employee * e: employees){
        if(isDeliverableByVehicle(e->getType(), request)){
            if(e->isReady() && e->getMaxCargo() >= request.getCargo() && e->getDist() != INF){
                eligibleEmployees.push_back(e);
            }
        }
    }
    return eligibleEmployees;
}

bool isDeliverableByVehicle(VehicleType vehicleType, const Request & request){
    if(vehicleType == FOOT || vehicleType == BIKE) return request.isDeliverableByFoot();
    else if(vehicleType == CAR || vehicleType == MOTORCYCLE)return request.isDeliverableByCar();
    else return false;
}

bool compareEmployees(Employee * e1, Employee * e2){
    return *e1 < *e2;
}

vector<Task*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees){
    vector<Task*> tasks;
    vector<Task*> roundTasks;
    min_priority_queue pendingRequests;
    int availableEmployees = employees.size();

    if(employees.empty()) return tasks;

    requests = setRequestsDeliverability(graph,reducedGraph,requests);

    while(!requests.empty()){

        setDistancesToCheckpoint(graph, reducedGraph, employees,requests.top());

        vector<Employee*> eligibleEmployees = getEligibleEmployees(employees, requests.top());

        if(eligibleEmployees.empty()){
            pendingRequests.push(requests.top());
        }
        else{
            sort(eligibleEmployees.begin(), eligibleEmployees.end(),compareEmployees);
            eligibleEmployees[0]->setReady(false);

            Task * task = new Task(eligibleEmployees[0], requests.top());
            availableEmployees--;
            roundTasks.push_back(task);
        }
        requests.pop();

        if(requests.empty()){

            if(!pendingRequests.empty() && availableEmployees == employees.size()){
                while(!pendingRequests.empty()){
                    roundTasks.push_back(new Task(nullptr,pendingRequests.top()));
                    pendingRequests.pop();
                }
            }

            requests = pendingRequests;
            availableEmployees = employees.size();

            while(!pendingRequests.empty())
                pendingRequests.pop();

            for(Task * task: roundTasks){
                if(task->getVehicleType() == BIKE || task->getVehicleType() == FOOT)
                    task->setFloydWarshallPath(reducedGraph);
                else if(task->getVehicleType() == CAR || task->getVehicleType() == MOTORCYCLE)
                    task->setFloydWarshallPath(graph);
            }
            tasks.insert(tasks.end(),roundTasks.begin(), roundTasks.end());
            roundTasks.clear();
        }
    }

    return tasks;
}
