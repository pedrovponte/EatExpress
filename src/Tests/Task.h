//
// Created by diana on 09/05/20.
//

#ifndef CAL_T3G4_TASK_H
#define CAL_T3G4_TASK_H


#include "Employee.h"
#include "Request.h"

class Task {
    Employee employee;
    Request request;
    vector<Coordinates> path;
public:
    Task(const Employee &employee, const Request &request);
    void setFloydWarshallPath(Graph<Coordinates> & graph);
    const vector<Coordinates> getPath() const;
};


#endif //CAL_T3G4_TASK_H
