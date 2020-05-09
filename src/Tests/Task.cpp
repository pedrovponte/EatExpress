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
}

const vector<Coordinates> Task::getPath() const{
    return path;
}