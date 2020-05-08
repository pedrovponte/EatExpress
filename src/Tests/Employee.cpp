//
// Created by pedro on 08/05/2020.
//

#include "Employee.h"

using namespace std;

Employee::Employee(unsigned long id, const Coordinates &coordinates, int maxCargo, char type, bool ready)
    : id(id), coordinates(coordinates), maxCargo(maxCargo),type(type),ready(ready) {}

unsigned long Employee::getId() const {
    return id;
}

void Employee::setId(unsigned long id) {
    this->id = id;
}

const Coordinates &Employee::getCoordinates() const {
    return coordinates;
}

void Employee::setCoordinates(const Coordinates &coordinates) {
    this->coordinates = coordinates;
}

int Employee::getMaxCargo() const {
    return maxCargo;
}

void Employee::setMaxCargo(int maxCargo) {
    this->maxCargo = maxCargo;
}

char Employee::getType() const {
    return type;
}

void Employee::setType(char type) {
    this->type = type;
}

bool Employee::isReady() const {
    return ready;
}

void Employee::setReady(bool ready) {
    this->ready = ready;
}
