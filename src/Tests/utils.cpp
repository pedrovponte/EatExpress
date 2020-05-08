//
// Created by diana on 06/05/20.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <edgetype.h>
#include "utils.h"

using namespace std;

double euclideanDistance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2,2) + pow(y1-y2,2));
}

double haversineDistance(double lat1, double long1, double lat2, double long2){
    double earthRad = 6371000; // meters
    double p1 = lat1 * M_PI / 180;
    double p2 = lat2 * M_PI / 180;

    double dp = (lat2-lat1) * M_PI / 180;
    double dt = (long2-long1) * M_PI / 180;
    double a = sin(dp / 2) * sin(dp / 2) +
            cos(p1) * cos(p2) * sin(dt / 2) * sin(dt / 2);


    double c = 2 * atan2(sqrt(a),sqrt(1-a));

    return earthRad * c; // in metres
}

Graph<Coordinates> loadGraph(string dir, string subDir, bool euclidean){
    istringstream ss;
    stringstream edgesFile, nodesFile;
    Graph<Coordinates> g;
    string firstLine;

    edgesFile << "../Mapas/" << dir << "/" << subDir;
    nodesFile << "../Mapas/" << dir << "/" << subDir;

    if(dir == "GridGraphs"){
        edgesFile << "/edges.txt";
        nodesFile << "/nodes.txt";
    }
    else{
        transform(subDir.begin(), subDir.end(), subDir.begin(), ::tolower);

        edgesFile << "/edges_" << subDir << ".txt";
        nodesFile << "/nodes_lat_lon" << subDir << ".txt";
    }

    ifstream nodes, edges;

    nodes.open(nodesFile.str());
    int i = 0;
    if (nodes.is_open()) {
        getline(nodes, firstLine);
        while(i < stoi(firstLine)){
            string node;
            unsigned long id;
            double latitude, longitude;

            getline(nodes, node, ',');
            ss.clear();
            ss.str(node.substr(1,node.length() - 1));
            ss >> id;

            getline(nodes, node, ',');
            ss.clear();
            ss.str(node);
            ss >> latitude;

            getline(nodes, node);
            ss.clear();
            ss.str(node.substr(0,node.length() - 1));
            ss >> longitude;

            g.addVertex(Coordinates(id,latitude, longitude));
            i++;
        }
    }
    nodes.close();

    i = 0;
    edges.open(edgesFile.str());

    if (edges.is_open()) {
        getline(edges, firstLine);
        while(i < stoi(firstLine)){
            string edge;
            unsigned long origId, destId;

            getline(edges, edge, ',');
            ss.clear();
            ss.str(edge.substr(1,edge.length() - 1));
            ss >> origId;

            getline(edges, edge);
            ss.clear();
            ss.str(edge.substr(0,edge.length() - 1));
            ss >> destId;

            Coordinates origCoords(origId);
            Coordinates destCoords(destId);

            Vertex<Coordinates> * v1 = g.findVertex(origCoords);
            Vertex<Coordinates> * v2 = g.findVertex(destCoords);

            double dist;

            if (euclidean)
                dist = euclideanDistance(v1->getInfo().getLatitude(),v1->getInfo().getLongitude(),v2->getInfo().getLatitude(),v2->getInfo().getLongitude());
            else
                dist = haversineDistance(v1->getInfo().getLatitude(), v1->getInfo().getLongitude(), v2->getInfo().getLatitude(), v2->getInfo().getLongitude());

            g.addEdge(origCoords, destCoords, dist);
            i++;
        }
    }
    edges.close();

    return g;
}

void viewFileGraph(GraphViewer *gv, string dir, string subDir, bool euclidean){
    istringstream ss;
    stringstream edgesFile, nodesFile;
    Graph<Coordinates> g;
    string firstLine;

    edgesFile << "../Mapas/" << dir << "/" << subDir;
    nodesFile << "../Mapas/" << dir << "/" << subDir;

    if(dir == "GridGraphs"){
        edgesFile << "/edges.txt";
        nodesFile << "/nodes.txt";
    }
    else{
        transform(subDir.begin(), subDir.end(), subDir.begin(), ::tolower);

        edgesFile << "/edges_" << subDir << ".txt";
        nodesFile << "/nodes_x_y_" << subDir << ".txt";
    }

    ifstream nodes, edges;

    nodes.open(nodesFile.str());
    int i = 0;
    if (nodes.is_open()) {
        getline(nodes, firstLine);
        while(i < stoi(firstLine)){
            string node;
            unsigned long id;
            double x, y;

            getline(nodes, node, ',');
            ss.clear();
            ss.str(node.substr(1,node.length() - 1));
            ss >> id;

            getline(nodes, node, ',');
            ss.clear();
            ss.str(node);
            ss >> x;

            getline(nodes, node);
            ss.clear();
            ss.str(node.substr(0,node.length() - 1));
            ss >> y;

            g.addVertex(Coordinates(id,x, y));
            gv->addNode(id,x,y);
            gv->setVertexLabel(id, to_string(id));

            i++;
        }
    }
    nodes.close();

    i = 0;
    edges.open(edgesFile.str());

    if (edges.is_open()) {
        getline(edges, firstLine);
        while(i < stoi(firstLine)){
            string edge;
            unsigned long origId, destId;

            getline(edges, edge, ',');
            ss.clear();
            ss.str(edge.substr(1,edge.length() - 1));
            ss >> origId;

            getline(edges, edge);
            ss.clear();
            ss.str(edge.substr(0,edge.length() - 1));
            ss >> destId;

            Coordinates origCoords(origId);
            Coordinates destCoords(destId);

            Vertex<Coordinates> * v1 = g.findVertex(origCoords);
            Vertex<Coordinates> * v2 = g.findVertex(destCoords);

            double dist;

            if (euclidean)
                dist = euclideanDistance(v1->getInfo().getLatitude(),v1->getInfo().getLongitude(),v2->getInfo().getLatitude(),v2->getInfo().getLongitude());
            else
                dist = haversineDistance(v1->getInfo().getLatitude(), v1->getInfo().getLongitude(), v2->getInfo().getLatitude(), v2->getInfo().getLongitude());

            gv->addEdge(i, origId, destId, EdgeType::DIRECTED);
            gv->setEdgeLabel(i,"Dist: " + to_string(dist));
            //gv->setEdgeWeight(i,dist)
            i++;
        }
    }
    edges.close();
}

void viewDijkstraShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, Coordinates orig, const Coordinates & dest){
    graph.dijkstraShortestPath(orig);
    vector<Coordinates> path = graph.getPathTo(dest);

    Vertex<Coordinates> * v;
    for(unsigned int i = 0; i < path.size()-1; i++) {
        gv->addNode(path[i].getId(), path[i].getLatitude(), path[i].getLongitude());
        v = graph.findVertex(path[i].getId());

        gv->setVertexLabel(path[i].getId(),"Id: " + to_string(path[i].getId())+ "  Dist: " + to_string(v->getDist()));

        if(i != 0){
            gv->addEdge(i,path[i-1].getId(),path[i].getId(),EdgeType::DIRECTED);
        }
    }
}

void viewFloydWarshallShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, const Coordinates & orig, const Coordinates & dest){
    double dist = 0;
    double ** W;

    graph.floydWarshallShortestPath();
    vector<Coordinates> path = graph.getfloydWarshallPath(orig, dest);
    W = graph.getDistancesMatrix();

    int origIdx, destIdx;
    for(unsigned int i = 0; i < path.size(); i++) {

        gv->addNode(path[i].getId(), path[i].getLatitude(), path[i].getLongitude());

        if(i == 0){
            origIdx = graph.findVertexIdx(path[i]);
            destIdx = origIdx;
        }
        else{
            origIdx = graph.findVertexIdx(path[i-1]);
            destIdx = graph.findVertexIdx(path[i]);
        }
        dist += W[origIdx][destIdx];

        gv->setVertexLabel(path[i].getId(),"Id: " + to_string(path[i].getId())+ "  Dist: " + to_string(dist));

        if(i != 0){
            gv->addEdge(i,path[i-1].getId(),path[i].getId(),EdgeType::DIRECTED);
        }
    }
}

void graphViewerProperties(GraphViewer * gv){
    gv->createWindow(700, 700);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
}
