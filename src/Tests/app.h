//
// Created by pedro on 15/05/2020.
//

#ifndef CAL_T3G4_APP_H
#define CAL_T3G4_APP_H

#include "Coordinates.h"
#include "Graph.h"
#include "Request.h"
#include "SpecialTask.h"

Request makeRequest(Graph<Coordinates> & graph);
int deliveryRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, Request & r);

int grid4x4();
int grid8x8();
int grid16x16();
int grid20x20();
int grid30x30();

int chooseMap();

int simulationMenu(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph);
int simultaneousRequestsSimulation(Graph<Coordinates> & graph);
int temporalOrderRequestsSimulation(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph);
min_priority_queue randomRequests1(unsigned number, unsigned vertices);
vector<Request> randomRequests2(unsigned number, unsigned vertices);
vector<Employee*> randomEmployees(unsigned number, unsigned vertices);
Employee * getRandomEmployee(unsigned vertices);

string restaurantType(VertexType v);

char singleRequest();
bool previewCity();

#endif //CAL_T3G4_APP_H
