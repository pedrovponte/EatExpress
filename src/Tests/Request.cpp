//
// Created by pedro on 08/05/2020.
//

#include "Request.h"

template<class T>
Request<T>::Request(unsigned long id, const Date &requestDate, const Hour &requestHour,
                    const list<Vertex<T>> &checkpoints, int cargo):id(id), request_date(requestDate),
                                                                   request_hour(requestHour), checkpoints(checkpoints),
                                                                   cargo(cargo) {}

template<class T>
unsigned long Request<T>::getId() const {
    return id;
}

template<class T>
void Request<T>::setId(unsigned long id) {
    Request::id = id;
}

template<class T>
const Date &Request<T>::getRequestDate() const {
    return request_date;
}

template<class T>
void Request<T>::setRequestDate(const Date &requestDate) {
    request_date = requestDate;
}

template<class T>
const Hour &Request<T>::getRequestHour() const {
    return request_hour;
}

template<class T>
void Request<T>::setRequestHour(const Hour &requestHour) {
    request_hour = requestHour;
}

template<class T>
const list<Vertex<T>> &Request<T>::getCheckpoints() const {
    return checkpoints;
}

template<class T>
void Request<T>::setCheckpoints(const list<Vertex<T>> &checkpoints) {
    Request::checkpoints = checkpoints;
}

template<class T>
int Request<T>::getCargo() const {
    return cargo;
}

template<class T>
void Request<T>::setCargo(int cargo) {
    Request::cargo = cargo;
}
