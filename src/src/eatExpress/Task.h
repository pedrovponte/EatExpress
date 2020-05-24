//
// Created by Diana Freitas on 19/05/2020.
//

#ifndef CAL_T3G4_TASK_H
#define CAL_T3G4_TASK_H

#include "../graph/Graph.h"
#include "../eatExpress/Employee.h"
#include <vector>

using namespace std;

class Task {
protected:
    Employee * employee;
    vector<Coordinates> path;
    double totalDistance;
    int id;
public:
    Task(Employee *  employee, int id);
    const vector<Coordinates> getPath() const;
    VehicleType getVehicleType() const;
    Employee *getEmployee() const;
    int getId() const;
};


#endif //CAL_T3G4_TASK_H
