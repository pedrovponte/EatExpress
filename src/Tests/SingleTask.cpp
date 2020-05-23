//
// Created by diana on 09/05/20.
//

#include <sstream>
#include <cmath>
#include "SingleTask.h"

// SingleTask class

SingleTask::SingleTask(Employee * employee, Request request, int id) : Task(employee,id), request(request) {
    this->time = 0;
}

void SingleTask::setFloydWarshallPath(Graph<Coordinates> & graph){
    Coordinates orig = employee->getCoordinates();
    vector<Coordinates> tempPath;
    totalDistance = 0;

    int i = 0;
    for(Coordinates checkpoint: request.getCheckpoints()){
        tempPath = graph.getfloydWarshallPath(orig, checkpoint);
        totalDistance += graph.getDist(graph.findVertexIdx(orig), graph.findVertexIdx(checkpoint));

        if(i == 0) path = tempPath;
        else path.insert(path.end(),tempPath.begin()+1, tempPath.end());

        orig = checkpoint;
        i++;
    }

    Coordinates dest = request.getDeliveryAddr();

    tempPath = graph.getfloydWarshallPath(orig, dest);
    totalDistance += graph.getDist(graph.findVertexIdx(orig), graph.findVertexIdx(dest));

    path.insert(path.end(),tempPath.begin()+1, tempPath.end());

    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);

    time = ceil((totalDistance * 60) / (1000 * employee->getAvgVelocity()));
}

void SingleTask::setDijkstraPath(Graph<Coordinates> & graph){
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

bool SingleTask::isCheckpoint(Coordinates coordinates){
    vector<Coordinates> checkpoints = request.getCheckpoints();
    for(int i = 0; i< checkpoints.size(); i++){
        if(checkpoints[i] == coordinates)
            return true;
    }
    return false;
}

bool SingleTask::isDeliveryAddress(Coordinates coordinates){
    return request.getDeliveryAddr() == coordinates;
}

std::ostream &operator<<(std::ostream &os, const SingleTask &task){
    if(task.employee == nullptr){
        os << "\t" << task.request;
        os << "\tRequest couldn't be completed! Check if the Vertex you picked really exists!"<< endl;
        return os;
    }

    os << "\t" << task.request;
    os << "\t" << *task.employee<< endl;

    if(!task.path.empty())
        os << "\tInitial Employee's Position: " << task.path[0] << endl;

    os << "\tTotal distance: " << task.totalDistance << " m" << endl;

    return os;
}

string SingleTask::pathToString(){
    ostringstream os;

    os << "\tPath: ";
    for(unsigned int i = 0; i < path.size(); i++)
        os << path[i] << " ";
    os << endl;

    return os.str();
}

bool  SingleTask::operator <(const SingleTask & task){
    if(this->getVehicleType() != INVALID && task.getVehicleType() != INVALID){
        if(employee->getId() == task.employee->getId()){
            return id < task.getId();
        }
        return employee->getId() < task.employee->getId();
    }

    return(this->getVehicleType() != INVALID && task.getVehicleType() == INVALID);
}

const Request & SingleTask::getRequest() const {
    return request;
}

int SingleTask::getTime() const {
    return time;
}

bool compareTasks(SingleTask * t1, SingleTask * t2){
    return *t1 < *t2;
}

// Request distribution Phase 2

vector<SingleTask*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    int origIdx, destIdx;
    double dist;
    vector<SingleTask*> tasks;
    int taskId = 0;
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
        tasks.push_back(new SingleTask(&employees[employeeIdx], requests.front(), taskId)); // Create new task for the request
        taskId++;
        requests.pop();
    }
    return tasks;
}

vector<SingleTask*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    vector<SingleTask*> tasks;
    int taskId = 0;
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
        tasks.push_back(new SingleTask(&employees[employeeIdx], requests.front(), taskId)); // Create new task for the request
        taskId++;
        requests.pop();
    }
    return tasks;
}


/**************** Distribute Requests among Employees - Phase 3  ***************/

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
        else
            request.setDeliverableByCar(false);

        // Also check if the distance is not over the limit of 6km - for bikes and employees that travel by foot
        if(origIdx2 != -1 && destIdx2 != -1 && reducedGraph.getDist(origIdx2,destIdx2) <= 6000)
            request.setDeliverableByFoot(true);
        else
            request.setDeliverableByFoot(false);

        requestsQueue.push(request);
    }

    return requestsQueue;
}

void setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request){
    int origIdx;
    int checkpointIdx1 = graph.findVertexIdx(request.getCheckpoints()[0]);
    int checkpointIdx2 = reducedGraph.findVertexIdx(request.getCheckpoints()[0]);

    for(Employee * e : employees){
        if(e->getType() == CAR || e->getType() == MOTORCYCLE){
            origIdx =  graph.findVertexIdx(e->getCoordinates());
            if(origIdx != -1 && checkpointIdx1 != -1)
                e->setDist(graph.getDist(origIdx, checkpointIdx1));
            else
                request.setDeliverableByCar(false);

        }
        else if(e->getType() == BIKE || e->getType() == FOOT){
            origIdx =  reducedGraph.findVertexIdx(e->getCoordinates());
            // Also check if the distance is not over the limit of 6km - for bikes and employees that travel by foot
            if(origIdx != -1 && checkpointIdx2 != -1 && reducedGraph.getDist(origIdx, checkpointIdx2) <= 6000)
                e->setDist(reducedGraph.getDist(origIdx, checkpointIdx2));
            else{
                request.setDeliverableByFoot(false);
            }
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
    if(vehicleType == FOOT || vehicleType == BIKE){
        return request.isDeliverableByFoot();
    }
    else if(vehicleType == CAR || vehicleType == MOTORCYCLE)return request.isDeliverableByCar();
    else return false;
}

vector<SingleTask*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees){
    vector<SingleTask*> tasks;
    int taskId = 0;
    vector<SingleTask*> roundTasks;
    min_priority_queue pendingRequests;
    int availableEmployees = employees.size();

    if(employees.empty()) return tasks;

    requests = setRequestsDeliverability(graph,reducedGraph,requests);

    while(!requests.empty()){
        Request r = requests.top();
        requests.pop();

        setDistancesToCheckpoint(graph, reducedGraph, employees,r);

        vector<Employee*> eligibleEmployees = getEligibleEmployees(employees, r);

        if(eligibleEmployees.empty()){
            pendingRequests.push(r);
        }
        else{
            sort(eligibleEmployees.begin(), eligibleEmployees.end(),compareEmployees);
            eligibleEmployees[0]->setReady(false);

            SingleTask * task = new SingleTask(eligibleEmployees[0], r, taskId);
            taskId++;
            availableEmployees--;
            roundTasks.push_back(task);
        }


        if(requests.empty()){
            if(!pendingRequests.empty() && availableEmployees == employees.size()){
                while(!pendingRequests.empty()){
                    roundTasks.push_back(new SingleTask(nullptr, pendingRequests.top(), taskId));
                    pendingRequests.pop();
                    taskId++;
                }
            }

            requests = pendingRequests;
            availableEmployees = employees.size();

            while(!pendingRequests.empty())
                pendingRequests.pop();

            for(SingleTask * task: roundTasks){
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

/**************** Multiple Restaurants Request  ***************/

vector<Employee*> getEligibleEmployeesMultipleRestaurants(vector<Employee*> & employees, const Request & request){
    vector<Employee*> eligibleEmployees;

    for(Employee * e: employees){
        if(e->isReady() && e->getMaxCargo() >= request.getCargo()){
            eligibleEmployees.push_back(e);
        }
    }
    return eligibleEmployees;
}

int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants){
    int origIdx = graph.findVertexIdx(origin);
    int destIdx, nearestRestaurantPos=-1;
    double nearestRestaurantDist = INF;

    int i = 0;
    for(Coordinates restaurant: restaurants){
        destIdx = graph.findVertexIdx(restaurant);

        if(destIdx == -1 || origIdx == -1)
            return -1;

        if(graph.getDist(origIdx,destIdx) < nearestRestaurantDist){
            nearestRestaurantDist = graph.getDist(origIdx,destIdx);
            nearestRestaurantPos = i;
        }
        i++;
    }

    return nearestRestaurantPos;
}

SingleTask * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request){
    vector<Coordinates> restaurants;
    int taskId = 0;

    int nearestRestaurantPos, nearestEmployeePos;
    double nearestEmployeeDist = INF;

    employees = getEligibleEmployeesMultipleRestaurants(employees, request);

    for(int i = 0; i< employees.size(); i++){
        double totalDist = 0;
        Coordinates origin = employees[i]->getCoordinates();
        vector<Coordinates> requestRestaurants = request.getCheckpoints();
        vector<Coordinates> restaurantsPath;

        for(int j = 0; j < request.getCheckpoints().size(); j++){
            double dist = 0;
            if(employees[i]->getType() == CAR ||employees[i]->getType() == MOTORCYCLE){
                nearestRestaurantPos = getNearestRestaurant(graph,origin, requestRestaurants);
                // One of the restaurants does not exist
                if(nearestRestaurantPos == -1)
                    return new SingleTask(nullptr, request, taskId);

                dist = graph.getDist(graph.findVertexIdx(origin),graph.findVertexIdx(requestRestaurants[nearestRestaurantPos]));

                // No path found for this employee
                if(dist == INF){
                    totalDist = INF;
                    break;
                }
            }
            else if (employees[i]->getType() == BIKE || employees[i]->getType() == FOOT){
                nearestRestaurantPos = getNearestRestaurant(reducedGraph,origin, requestRestaurants);
                // One of the restaurants does not exist
                if(nearestRestaurantPos == -1){
                    totalDist = INF;
                    break;
                }

                dist = reducedGraph.getDist(reducedGraph.findVertexIdx(origin),reducedGraph.findVertexIdx(requestRestaurants[nearestRestaurantPos]));

                // No path found for this employee
                if(dist == INF){
                    totalDist = INF;
                    break;
                }
            }

            totalDist += dist;
            restaurantsPath.push_back(requestRestaurants[nearestRestaurantPos]);
            origin = requestRestaurants[nearestRestaurantPos];
            requestRestaurants.erase(requestRestaurants.begin()+nearestRestaurantPos);
        }

        if(totalDist == INF || (totalDist > 6000 && (employees[i]->getType() == BIKE || employees[i]->getType() == FOOT))){
            continue;
        }

        // Check if path from last restaurant to delivery address exists
        if(employees[i]->getType() == CAR || employees[i]->getType() == MOTORCYCLE){
            int deliveryIdx = graph.findVertexIdx(request.getDeliveryAddr());
                if(deliveryIdx != -1){
                    double dist = graph.getDist(graph.findVertexIdx(restaurantsPath[restaurantsPath.size()-1]),deliveryIdx);
                    if(dist == INF) break;
                    totalDist += dist;
                } else break;
        }
        else if (employees[i]->getType() == BIKE || employees[i]->getType() == FOOT){
            int deliveryIdx = reducedGraph.findVertexIdx(request.getDeliveryAddr());
            if(deliveryIdx != -1){
                double dist = reducedGraph.getDist(reducedGraph.findVertexIdx(restaurantsPath[restaurantsPath.size()-1]),deliveryIdx);
                if(dist == INF || totalDist + dist > 6000) break;
                totalDist += dist;
            } else break;
        }

        if(totalDist < nearestEmployeeDist){
            nearestEmployeePos = i;
            nearestEmployeeDist = totalDist;
            restaurants = restaurantsPath;
        }
    }

    if(nearestEmployeeDist == INF) return new SingleTask(nullptr, request, taskId);

    request.setCheckpoints(restaurants);

    SingleTask * task =  new SingleTask(employees[nearestEmployeePos], request, taskId);

    if(task->getVehicleType() == CAR || task->getVehicleType() == MOTORCYCLE)
        task->setFloydWarshallPath(graph);
    else if (task->getVehicleType() == BIKE || task->getVehicleType() == FOOT)
        task->setFloydWarshallPath(reducedGraph);

    return task;
}