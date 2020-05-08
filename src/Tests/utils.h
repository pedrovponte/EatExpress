//
// Created by diana on 06/05/20.
//

#ifndef CAL_T3G4_UTILS_H
#define CAL_T3G4_UTILS_H

#include "Graph.h"
#include <graphviewer.h>
#include <string>

using namespace std;

double euclideanDistance(double x1, double y1, double x2, double y2);
double haversineDistance(double lat1, double long1, double lat2, double long2);

Graph<Coordinates> loadGraph(string folder, string subFolder, bool euclidean);
void viewFileGraph(GraphViewer *gv, string dir, string subDir, bool euclidean);

void viewDijkstraShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, Coordinates orig, const Coordinates & dest);

void viewFloydWarshallShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, const Coordinates & orig, const Coordinates & dest);

void graphViewerProperties(GraphViewer * gv);

#endif //CAL_T3G4_UTILS_H
