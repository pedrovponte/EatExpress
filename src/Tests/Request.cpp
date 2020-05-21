//
// Created by pedro on 08/05/2020.
//

#include "Request.h"

using namespace std;

Request::Request(unsigned long id, const Date &requestDate, const Hour &requestHour, int cargo): id(id), request_date(requestDate),request_hour(requestHour), cargo(cargo) {
    this->deliverableByFoot = false;
    this->deliverableByCar = false;
}

Request::Request(unsigned long id, const Date &requestDate, const Hour &requestHour,vector<Coordinates> checkpoints, Coordinates delivery_addr,
        int cargo): Request(id,requestDate,requestHour,cargo){
        this->checkpoints = checkpoints;
        this->delivery_addr = delivery_addr;
}

Request::Request(unsigned long id, const Date &requestDate, const Hour &requestHour,Coordinates checkpoint, Coordinates delivery_addr, int cargo): Request(id,requestDate,requestHour,cargo){
    this->checkpoints.push_back(checkpoint);
    this->delivery_addr = delivery_addr;
}

Request::Request(const Request & request): id(request.getId()), request_date(request.getRequestDate()), request_hour(request.getRequestHour()), cargo(request.getCargo()){
    this->checkpoints = request.checkpoints;
    this->delivery_addr = request.getDeliveryAddr();
    this->deliverableByFoot = request.isDeliverableByFoot();
    this->deliverableByCar = request.isDeliverableByCar();
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


vector<Coordinates> Request::getCheckpoints() const {
    return checkpoints;
}


void Request::addCheckpoint(Coordinates checkpoint) {
    checkpoints.push_back(checkpoint);
}


int Request::getCargo() const {
    return cargo;
}


void Request::setCargo(int cargo) {
    Request::cargo = cargo;
}


Coordinates Request::getDeliveryAddr() const {
    return delivery_addr;
}

void Request::setDeliveryAddr(Coordinates delivery_addr){
   this->delivery_addr = delivery_addr;
}

bool Request::operator<(const Request & request) const {
    if(this->request_date == request.getRequestDate())
        return this->request_hour < request.getRequestHour();
    else
        return this->request_date < request.getRequestDate();
}

std::ostream &operator<<(std::ostream &os, const Request & request) {
    os << "Request: Id = " << request.getId() << "; Restaurants = ";

    for(int i = 0; i < request.getCheckpoints().size();i++){
        os << request.getCheckpoints()[i] << " ";
    }

    os << "; Delivery address = " << request.getDeliveryAddr() << "; Cargo = " << request.getCargo() << "; Date: " << request.request_date
    << "; Hour: " <<request.request_hour << endl;

    return os;
}

bool Request::isDeliverableByFoot() const {
    return deliverableByFoot;
}

void Request::setDeliverableByFoot(bool deliverable) {
    Request::deliverableByFoot = deliverable;
}

bool Request::isDeliverableByCar() const {
    return deliverableByCar;
}

void Request::setDeliverableByCar(bool deliverable) {
    Request::deliverableByCar = deliverable;
}

void Request::setCheckpoints(const vector<Coordinates> &checkpoints) {
    Request::checkpoints = checkpoints;
}

void Request::setCheckpoint(const Coordinates &checkpoint) {
    checkpoints.clear();
    checkpoints.push_back(checkpoint);
}

bool requestsById(const Request & r1, const Request & r2){
    return r1.getId()<r2.getId();
}
