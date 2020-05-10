//
// Created by pedro on 08/05/2020.
//

#ifndef CAL_T3G4_EMPLOYEE_H
#define CAL_T3G4_EMPLOYEE_H

#include "Coordinates.h"
using namespace std;

enum vehicleType{CAR, BIKE, FOOT, INVALID};

class Employee {
    int id;
    Coordinates coordinates;
    int maxCargo;
    vehicleType type;
    bool ready;
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

    friend std::ostream &operator<<(std::ostream &os, const Employee & employee);

};

#endif //CAL_T3G4_EMPLOYEE_H
