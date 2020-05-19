#include "Task.h"

//
// Created by Diana Freitas on 19/05/2020.
//
Task::Task(Employee *employee, int id) : employee(employee), id(id) {}

const vector<Coordinates> Task::getPath() const{
    return path;
}

VehicleType Task::getVehicleType() const{
    if(employee == nullptr)
        return INVALID;
    return employee->getType();
}

Employee *Task::getEmployee() const {
    return employee;
}

int Task::getId() const {
    return id;
}

