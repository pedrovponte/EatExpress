//
// Created by pedro on 15/05/2020.
//

#ifndef CAL_T3G4_APP_H
#define CAL_T3G4_APP_H

#include "Coordinates.h"
#include "Graph.h"
#include "Request.h"

Request make_request(Graph<Coordinates> graph);
int deliveryRequests(Graph<Coordinates> graph, Graph<Coordinates> reducedGraph, Request r);
int grid4x4();
int grid8x8();
int grid16x16();
int grid20x20();
int grid30x30();
int chooseMap();

string restaurantType(VertexType v);

bool previewCity();

#endif //CAL_T3G4_APP_H
