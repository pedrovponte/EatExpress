//
// Created by pedro on 08/05/2020.
//

#include "Request.h"

using namespace std;

Request::Request(unsigned long id, const Date &requestDate, const Hour &requestHour, int cargo): id(id), request_date(requestDate),request_hour(requestHour), cargo(cargo) {}

Request::Request(unsigned long id, const Date &requestDate, const Hour &requestHour,vector<Vertex<Coordinates>*> checkpoints, Vertex<Coordinates>* delivery_addr,
        int cargo): Request(id,requestDate,requestHour,cargo){
        this->checkpoints = checkpoints;
        this->delivery_addr = delivery_addr;
}

unsigned long Request::getId() const {
    return id;
}


void Request::setId(unsigned long id) {
    Request::id = id;
}


const Date &Request::getRequestDate() const {
    return request_date;
}


void Request::setRequestDate(const Date &requestDate) {
    request_date = requestDate;
}


const Hour &Request::getRequestHour() const {
    return request_hour;
}


void Request::setRequestHour(const Hour &requestHour) {
    request_hour = requestHour;
}


vector<Vertex<Coordinates>*> Request::getCheckpoints() const {
    return checkpoints;
}


void Request::addCheckpoint(Vertex<Coordinates> * checkpoint) {
    checkpoints.push_back(checkpoint);
}


int Request::getCargo() const {
    return cargo;
}


void Request::setCargo(int cargo) {
    Request::cargo = cargo;
}


Vertex<Coordinates> *Request::getDeliveryAddr() const {
    return delivery_addr;
}

void Request::setDeliveryAddr(Vertex<Coordinates> * delivery_addr){
   this->delivery_addr = delivery_addr;
}