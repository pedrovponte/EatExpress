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

vector<Task*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees){
    graph.floydWarshallShortestPath();

    double ** W = graph.getDistancesMatrix();
    int origIdx, destIdx;
    Employee employee;
    double dist = INF;
    vector<Task*> tasks;

    vector<Employee>::iterator it;
    vector<Employee>::iterator del;
    while(!requests.empty() && !employees.empty()){
        Request request = requests.front();
        requests.pop();

        destIdx = graph.findVertexIdx(request.getCheckpoints()[0]->getInfo());

        for(it = employees.begin(); it != employees.end(); it ++){
            origIdx = graph.findVertexIdx(it->getCoordinates());

            if(dist > W[origIdx][destIdx]){
                employee = Employee(*it);
                del = it;
                dist = W[origIdx][destIdx];
            }
        }
        employees.erase(del);
        tasks.push_back(new Task(employee,request));
    }

    return tasks;
}