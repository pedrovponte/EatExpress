//
// Created by pedro on 08/05/2020.
//

#ifndef CAL_T3G4_REQUEST_H
#define CAL_T3G4_REQUEST_H

#include <iostream>
#include <list>
#include "Vertex.h"
#include "utils.h"
using namespace std;

template <class T>
class Request {
    unsigned long id;
    Date request_date;
    Hour request_hour;
    list<Vertex<T>> checkpoints;
    int cargo;
public:
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour, const list<Vertex<T>> &checkpoints,
            int cargo);
    unsigned long getId() const;
    void setId(unsigned long id);
    const Date &getRequestDate() const;
    void setRequestDate(const Date &requestDate);
    const Hour &getRequestHour() const;
    void setRequestHour(const Hour &requestHour);
    const list<Vertex<T>> &getCheckpoints() const;
    void setCheckpoints(const list<Vertex<T>> &checkpoints);
    int getCargo() const;
    void setCargo(int cargo);
};

#endif //CAL_T3G4_REQUEST_H
