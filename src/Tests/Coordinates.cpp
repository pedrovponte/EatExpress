//
// Created by diana on 06/05/20.
//

#include "Coordinates.h"

Coordinates::Coordinates(unsigned long id) : Coordinates(id,0, 0) {
}

Coordinates::Coordinates(unsigned long id, double latitude, double longitude)
        : latitude(latitude), longitude(longitude), id(id) {}

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


