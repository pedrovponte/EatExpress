//
// Created by pedro on 08/05/2020.
//

#ifndef CAL_T3G4_REQUEST_H
#define CAL_T3G4_REQUEST_H

#include <iostream>
#include <list>
#include "../graph/Vertex.h"
#include "../utils/utils.h"

using namespace std;

class Request {
    unsigned long id;
    Date request_date;
    Hour request_hour;
    vector<Coordinates> checkpoints;
    Coordinates delivery_addr;
    int cargo;
    bool deliverableByFoot;
    bool deliverableByCar;
public:
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour, int cargo);
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour, vector<Coordinates> checkpoints, Coordinates delivery_addr, int cargo);
    Request(unsigned long id, const Date &requestDate, const Hour &requestHour,Coordinates checkpoint, Coordinates delivery_addr, int cargo);
    Request(const Request & request);
    unsigned long getId() const;
    void setId(unsigned long id);
    const Date &getRequestDate() const;
    void setRequestDate(const Date &requestDate);
    const Hour &getRequestHour() const;
    void setRequestHour(const Hour &requestHour);
    vector<Coordinates> getCheckpoints() const;
    Coordinates getDeliveryAddr() const;
    void setDeliveryAddr(Coordinates delivery_addr);
    void addCheckpoint(Coordinates checkpoint);
    void setCheckpoints(const vector<Coordinates> &checkpoints);
    void setCheckpoint(const Coordinates & checkpoint);
    int getCargo() const;
    void setCargo(int cargo);
    bool operator<(const Request & request) const;
    bool isDeliverableByFoot() const;
    void setDeliverableByFoot(bool deliverable);
    bool isDeliverableByCar() const;
    void setDeliverableByCar(bool deliverable);


    friend std::ostream &operator<<(std::ostream &os, const Request &request);
};

class requestComparator {
public:
    int operator()(const Request & r1, const Request & r2) {
        return r2 < r1;
    }
};

bool requestsById(const Request & r1, const Request & r2);

typedef priority_queue <Request, vector<Request>, requestComparator>  min_priority_queue;


#endif //CAL_T3G4_REQUEST_H
