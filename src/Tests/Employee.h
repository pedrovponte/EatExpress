//
// Created by pedro on 08/05/2020.
//

#ifndef CAL_T3G4_EMPLOYEE_H
#define CAL_T3G4_EMPLOYEE_H

#include "Coordinates.h"
using namespace std;

class Employee {
    unsigned long id;
    Coordinates coordinates;
    int maxCargo;
    char type;
    bool ready;
public:
    Employee(unsigned long id, const Coordinates &coordinates, int maxCargo, char type, bool ready);
    unsigned long getId() const;
    void setId(unsigned long id);
    const Coordinates &getCoordinates() const;
    void setCoordinates(const Coordinates &coordinates);
    int getMaxCargo() const;
    void setMaxCargo(int maxCargo);
    char getType() const;
    void setType(char type);
    bool isReady() const;
    void setReady(bool ready);

};

#endif //CAL_T3G4_EMPLOYEE_H
