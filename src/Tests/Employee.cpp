//
// Created by pedro on 08/05/2020.
//

#include "Employee.h"

using namespace std;

Employee::Employee(int id, const Coordinates &coordinates, int maxCargo, VehicleType type, bool ready)
    : id(id), coordinates(coordinates), maxCargo(maxCargo),type(type),ready(ready) {

    if(type == CAR || type == MOTORCYCLE){
        avgVelocity = 40;
    }
    else if(type == BIKE){
        avgVelocity = 20;
    }
    else if(type == FOOT){
        avgVelocity = 8;
    }
    avgVelocity = 0;
}

Employee::Employee(): id(-1), coordinates(0), maxCargo(-1),type(INVALID),ready(false) {}

Employee::Employee(const Employee &e): id(e.getId()), coordinates(e.getCoordinates()), maxCargo(e.getMaxCargo()),type(getType()),ready(e.isReady()) {


}

int Employee::getId() const {
    return id;
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

VehicleType Employee::getType() const {
    return type;
}

bool Employee::isReady() const {
    return ready;
}

void Employee::setReady(bool ready) {
    this->ready = ready;
}

bool Employee::operator==(const Employee &rhs) const {
    return id == rhs.id && type == rhs.type;
}


std::ostream &operator<<(std::ostream &os, const Employee & employee) {
    os << "EMPLOYEE: Id = " << employee.getId() << " Vehicle = ";

    string VehicleType;

    switch(employee.getType()) {
        case CAR:
            os << "Car";
            break;
        case MOTORCYCLE:
            os << "Motorcycle";
            break;
        case BIKE:
            os << "Bike";
            break;
        case FOOT:
            os << "By Foot";
            break;
        default:
            os << "Invalid";
            break;
    }

    os << "; MaxCargo = " << employee.getMaxCargo() << endl;

    return os;
}

bool Employee::operator<(const Employee &rhs) const {
    return dist*0.5 + maxCargo*0.3 + avgVelocity * 0.2 < rhs.getDist()*0.5 + rhs.getMaxCargo()* 0.3 + rhs.getAvgVelocity() * 0.2 ;
}

double Employee::getDist() const {
    return dist;
}

void Employee::setDist(double dist) {
    Employee::dist = dist;
}

int Employee::getAvgVelocity() const {
    return avgVelocity;
}
