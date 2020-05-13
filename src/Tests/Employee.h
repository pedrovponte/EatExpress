//
// Created by pedro on 08/05/2020.
//

#ifndef CAL_T3G4_EMPLOYEE_H
#define CAL_T3G4_EMPLOYEE_H

#include "Coordinates.h"
using namespace std;

enum vehicleType{CAR, MOTORCYCLE, BIKE, FOOT, INVALID};

class Employee {
    int id;
    Coordinates coordinates;
    int maxCargo;
    vehicleType type;
    int avgVelocity;
    bool ready;
    double dist;
public:
    Employee();
    Employee(const Employee & e);
    Employee(int id, const Coordinates &coordinates, int maxCargo, vehicleType type, bool ready);
    int getId() const;
    void setId(int id);
    const Coordinates &getCoordinates() const;
    void setCoordinates(const Coordinates &coordinates);
    int getMaxCargo() const;
    void setMaxCargo(int maxCargo);
    vehicleType getType() const;
    void setType(vehicleType type);
    bool isReady() const;
    void setReady(bool ready);
    double getDist() const;
    void setDist(double dist);
    int getAvgVelocity() const;

    friend std::ostream &operator<<(std::ostream &os, const Employee & employee);

    bool operator==(const Employee &rhs) const;

    bool operator<(const Employee &rhs) const;

};

#endif //CAL_T3G4_EMPLOYEE_H
