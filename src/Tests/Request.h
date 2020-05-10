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

class Request {
    unsigned long id;
    Date request_date;
    Hour request_hour;
    vector<Vertex<Coordinates>*> checkpoints;
    Vertex<Coordinates> * delivery_addr;
    int cargo;
public:
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour, int cargo);
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour, vector<Vertex<Coordinates>*> checkpoints, Vertex<Coordinates>* delivery_addr, int cargo);
    Request(const Request & request);
    unsigned long getId() const;
    void setId(unsigned long id);
    const Date &getRequestDate() const;
    void setRequestDate(const Date &requestDate);
    const Hour &getRequestHour() const;
    void setRequestHour(const Hour &requestHour);
    vector<Vertex<Coordinates>*> getCheckpoints() const;
    Vertex<Coordinates> *getDeliveryAddr() const;
    void setDeliveryAddr(Vertex<Coordinates> * delivery_addr);
    void addCheckpoint(Vertex<Coordinates> * checkpoint);
    int getCargo() const;
    void setCargo(int cargo);
    bool operator<(Request & request) const;

    friend std::ostream &operator<<(std::ostream &os, const Request &request);
};

#endif //CAL_T3G4_REQUEST_H
