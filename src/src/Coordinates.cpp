//
// Created by diana on 06/05/20.
//

#include "Coordinates.h"
#include <algorithm>

using namespace std;

Coordinates::Coordinates(){

    id = INT32_MAX;
    latitude = 0;
    longitude = 0;
}

Coordinates::Coordinates(unsigned long id) : Coordinates(id,0, 0) {
}

Coordinates::Coordinates(unsigned long id, double latitude, double longitude)
        : latitude(latitude), longitude(longitude), id(id) {}

Coordinates::Coordinates(const Coordinates &c) {
    id = c.getId();
    latitude = c.getLatitude();
    longitude = c.getLongitude();
}

double Coordinates::getLatitude() const  {
    return this->latitude;
}

double Coordinates::getLongitude() const {
    return this->longitude;
}

unsigned long Coordinates::getId() const  {
    return this->id;
}

bool Coordinates::operator==(const Coordinates &rightCoord) const {
    return this->id == rightCoord.id;
}

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
    os << coordinates.id;
    return os;
}


