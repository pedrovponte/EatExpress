//
// Created by diana on 06/05/20.
//

#ifndef CAL_T3G4_COORDINATES_H
#define CAL_T3G4_COORDINATES_H


#include <ostream>

using namespace std;

class Coordinates {
    unsigned long id;           // unique id
    double latitude;            // latitude
    double longitude;           // longitude
public:
    Coordinates();
    Coordinates(unsigned long id);
    Coordinates(unsigned long id, double latitude, double longitude);
    Coordinates(const Coordinates & c);
    double getLatitude() const;
    double getLongitude() const ;
    unsigned long getId() const;
    bool operator==(const Coordinates &rightCoord) const;

    friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);
};


#endif //CAL_T3G4_COORDINATES_H
