//
// Created by pedro on 15/05/2020.
//

#ifndef CAL_T3G4_APP_H
#define CAL_T3G4_APP_H

#include "Coordinates.h"
#include "Graph.h"
#include "Request.h"

Request make_request(Graph<Coordinates> graph, Graph<Coordinates> reducedGraph);

void grid4x4();
void grid8x8();
void grid16x16();
void grid20x20();
void grid30x30();
int chooseMap();

string restaurantType(VertexType v);

bool previewCity();

#endif //CAL_T3G4_APP_H
