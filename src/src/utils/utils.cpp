//
// Created by diana on 06/05/20.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <edgetype.h>
#include "../utils/utils.h"
#include "../eatExpress/SingleTask.h"
#include "../eatExpress/SpecialTask.h"

using namespace std;

// Distances

double euclideanDistance(double x1, double y1, double x2, double y2){
    return (sqrt(pow(x1 - x2,2) + pow(y1 - y2,2)));
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

// Load Graphs and Tags

Graph<Coordinates> loadGraph(string dir, string subDir, bool euclidean, bool preview){

    // Create Graph Viewer
    GraphViewer *gv;

    if(preview){
        gv = new GraphViewer(700, 700, false);
        graphViewerProperties(gv);
    }

    istringstream ss;
    stringstream edgesFile, nodesFile, tagsFile;
    Graph<Coordinates> g;
    string firstLine;

    map<unsigned long, VertexType> vTypes;

    edgesFile << "../Mapas/" << dir;
    nodesFile << "../Mapas/" << dir;

    if(dir == "GridGraphs"){
        edgesFile << "/" << subDir << "/edges.txt";
        nodesFile << "/" << subDir << "/nodes.txt";
        tagsFile << "../Mapas/" << dir << "Tags/" << subDir.substr(0,5) << "/tags_" << subDir.substr(0,5) <<".txt";
    }
    else{
        subDir = dir;
        transform(subDir.begin(), subDir.end(), subDir.begin(), ::tolower);

        edgesFile << "/edges_" << subDir << ".txt";
        nodesFile << "/nodes_x_y_" << subDir << ".txt";
        tagsFile << "../Mapas/" << dir << "/tags_" << subDir <<".txt";
    }
    vTypes  = loadTags(tagsFile.str());
    g.setVTypes(vTypes);

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

            g.addVertex(Coordinates(id,latitude, longitude), vTypes[id]);

            if(preview){
                gv->addNode(id,latitude,longitude);
                gv->setVertexLabel(id, to_string(id));

                setRestaurantIcon(gv,vTypes[id],id);
            }

            i++;
        }
    }
    nodes.close();

    i = 0;
    edges.open(edgesFile.str());

    if (edges.is_open()) {
        getline(edges, firstLine);
        if(dir == "GridGraphs"){
            firstLine = to_string(stoi(firstLine)*2);
        }

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

            g.addEdge(i,origCoords, destCoords, dist);

            if(preview){
                gv->addEdge(i, origId, destId, EdgeType::DIRECTED);
            }

            if(dir == "GridGraphs"){
                i++;
                g.addEdge(i,destCoords, origCoords,dist);
                if(preview){
                    gv->addEdge(i, destId, origId, EdgeType::DIRECTED);
                }
            }

            i++;
        }
    }
    edges.close();

    cleanGraph(g);

    if(preview) gv->rearrange();

    return g;
}

map<unsigned long, VertexType> loadTags(string path){
    istringstream ss;
    string nCategories, category, nNodes;
    map<unsigned long, VertexType> tagsMap;

    ifstream tagsFile;
    tagsFile.open(path);

    int i;
    if (tagsFile.is_open()) {
        i = 0;
        getline(tagsFile, nCategories);

        while(i < stoi(nCategories)){
            getline(tagsFile,category);
            getline(tagsFile,nNodes);

            VertexType vType;
            if(category == "restaurant"){
                vType = RESTAURANT;
            }else if(category == "fast_food"){
                vType = FAST_FOOD;
            }else if(category == "vegetarian"){
                vType = VEGETARIAN;
            }else if(category == "pizza"){
                vType = PIZZA;
            }else{
                vType = OTHER;
            }

            string idStr;
            unsigned long id;
            int j = 0;
            while(j < stoi(nNodes)){
                getline(tagsFile, idStr);
                ss.str(idStr);
                ss >> id;
                ss.clear();
                tagsMap.insert(pair<unsigned long, VertexType>(id,vType));
                j++;
            }
            i++;
        }
    }
    tagsFile.close();

    return tagsMap;
}

void cleanGraph(Graph<Coordinates> &graph){

    vector<Vertex<Coordinates> *> vertexes;

    for (Vertex<Coordinates> *vertex : graph.getVertexSet()) {
        if(vertex->getAdj().size() > 0){
            vertexes.push_back(vertex);
        }
    }

    graph.setVertexSet(vertexes);
}

// Graphic Viewer

void viewSinglePath(const Graph<Coordinates> & graph, const vector<Coordinates> & path, VehicleType type){

    GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    drawGraph(gv,graph);

    for(unsigned int i = 0; i < path.size(); i++) {
        gv->clearVertexColor(path[i].getId());
        gv->setVertexColor(path[i].getId(),"red");

        if(i == 0){
            setVehicleIcon(gv,type,path[i].getId());
        }
        else{
            if(i == path.size()-1)
                gv->setVertexIcon(path[i].getId(),"../Mapas/icons/house.png");
        }

        gv->clearVertexLabel(path[i].getId());
        gv->setVertexLabel(path[i].getId(),"Id: " + to_string(path[i].getId()));

        if(i != 0){
            int edgeId = graph.getEdge(path[i-1].getId(),path[i].getId()).getId();
            gv->clearEdgeColor(edgeId);
            gv->clearEdgeLabel(edgeId);
            gv->setEdgeColor(edgeId,"red");
            gv->setEdgeThickness(edgeId,3);
        }
    }

    gv->rearrange();
}

void viewEmployeePath(const Graph<Coordinates> & graph, vector<SingleTask*> tasks){

    GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    drawGraph(gv,graph);

    int i = 0;
    sort(tasks.begin(), tasks.end(), compareTasks);
    for(SingleTask * task: tasks){
        vector<Coordinates> path = task->getPath();
        for(int j = 0; j< path.size();j++){

            gv->clearVertexColor(path[j].getId());
            gv->setVertexColor(path[j].getId(),"red");

            if(i == 0 && j == 0){
                setVehicleIcon(gv,task->getVehicleType(),path[j].getId());
            }
            else if(task->isCheckpoint(path[j])){
                setRestaurantIcon(gv,graph.findVertex(path[j])->getType(),path[j].getId());
            }
            else if(task->isDeliveryAddress(path[j])){
                gv->setVertexIcon(path[j].getId(),"../Mapas/icons/house.png");
            }

            if(j != 0){
                int edgeId = graph.getEdge(path[j-1].getId(),path[j].getId()).getId();
                gv->clearEdgeColor(edgeId);
                gv->clearEdgeLabel(edgeId);
                gv->setEdgeColor(edgeId,"red");
                gv->setEdgeThickness(edgeId,3);
            }
        }
        i++;
    }
    gv->rearrange();
}

void viewSpecialTask(const Graph<Coordinates> & graph, SpecialTask * task){
    vector<Coordinates> delivery_addresses = task->getDeliveryAddresses();

    GraphViewer *gv = new GraphViewer(700, 700, false);
    graphViewerProperties(gv);

    int i = 0;
    for(Coordinates c: task->getPath()){
        gv->clearVertexColor(c.getId());
        gv->setVertexColor(c.getId(),"red");

        if(i == 0){
            setVehicleIcon(gv,task->getVehicleType(),c.getId());
        }

        setRestaurantIcon(gv,graph.findVertex(c)->getType(),c.getId());

        if(find(delivery_addresses.begin(),delivery_addresses.end(), c) != delivery_addresses.end()){
            gv->setVertexIcon(c.getId(),"../Mapas/icons/house.png");
        }

        if(i != 0){
            int edgeId = graph.getEdge(task->getPath()[i-1].getId(),c.getId()).getId();
            gv->clearEdgeColor(edgeId);
            gv->clearEdgeLabel(edgeId);
            gv->setEdgeColor(edgeId,"red");
            gv->setEdgeThickness(edgeId,3);
        }
        i++;
    }

    drawGraph(gv,graph);

    gv->rearrange();
}

void viewEmployeesPaths(const Graph<Coordinates> & graph,const Graph<Coordinates> & reducedGraph,vector<SingleTask*> tasks){
    int id = -1;
    VehicleType vehicleType = INVALID;
    vector<SingleTask*> employeeTasks;

    sort(tasks.begin(), tasks.end(), compareTasks);

    for(SingleTask * task: tasks){
        // No employee assigned to the task
        if(task->getEmployee() == nullptr)
            cout << "The request nr " << task->getId() << " could not be completed by any of the employees!" << endl;

        // First task
        if(id == -1){
            id = task->getEmployee()->getId();
            vehicleType = task->getVehicleType();
        }

        if(id != task->getEmployee()->getId()){
            // View all tasks from the same employee
            if(vehicleType == CAR || vehicleType == MOTORCYCLE)
                viewEmployeePath(graph,employeeTasks);
            else if(vehicleType == FOOT || vehicleType == BIKE)
                viewEmployeePath(reducedGraph,employeeTasks);

            id = task->getEmployee()->getId();
            vehicleType = task->getVehicleType();
            employeeTasks.clear();
        }

        employeeTasks.push_back(task);
    }

    // View all tasks from the same employee
    if(vehicleType == CAR || vehicleType == MOTORCYCLE)
        viewEmployeePath(graph,employeeTasks);
    else if(vehicleType == FOOT || vehicleType == BIKE)
        viewEmployeePath(reducedGraph,employeeTasks);
}

void graphViewerProperties(GraphViewer * gv){
    gv->defineVertexSize(15);
    gv->createWindow(700, 700);
    gv->defineVertexColor("gray");
    gv->defineEdgeColor("gray");
}

void setRestaurantIcon(GraphViewer * gv, VertexType type, unsigned long id){
    switch(type){
        case RESTAURANT:
            gv->setVertexIcon(id,"../Mapas/icons/restaurant.png");
            break;
        case FAST_FOOD:
            gv->setVertexIcon(id,"../Mapas/icons/fast_food.png");
            break;
        case VEGETARIAN:
            gv->setVertexIcon(id,"../Mapas/icons/vegetarian.png");
            break;
        case PIZZA:
            gv->setVertexIcon(id,"../Mapas/icons/pizza.png");
            break;
        default:
            break;
    }
}

void setVehicleIcon(GraphViewer * gv, VehicleType type, unsigned long id){
    switch(type){
        case CAR:
            gv->setVertexIcon(id,"../Mapas/icons/car.png");
            break;
        case MOTORCYCLE:
            gv->setVertexIcon(id,"../Mapas/icons/motorcycle.png");
            break;
        case BIKE:
            gv->setVertexIcon(id,"../Mapas/icons/bike.png");
            break;
        case FOOT:
            gv->setVertexIcon(id,"../Mapas/icons/foot.png");
            break;
        default:
            break;
    }
}

void drawGraph(GraphViewer *gv, const Graph<Coordinates> & graph){
    vector<Vertex<Coordinates>*> v = graph.getVertexSet();

    for(int i = 0; i < v.size(); i++){
        gv->addNode(v[i]->getInfo().getId(),v[i]->getInfo().getLatitude(),v[i]->getInfo().getLongitude());

        gv->setVertexLabel(v[i]->getInfo().getId(), to_string(v[i]->getInfo().getId()));

        setRestaurantIcon(gv,v[i]->getType(),v[i]->getInfo().getId());
    }

    for(int i = 0; i < v.size(); i++){
        for(Edge<Coordinates> e : v[i]->getAdj()){
            gv->addEdge(e.getId(), v[i]->getInfo().getId(),e.getDest()->getInfo().getId(),EdgeType::DIRECTED);
            //gv->setEdgeLabel(e.getId(),"Dist: " + to_string(e.getWeight()));
        }
    }
}

// Stubs and utils for test functions

vector<Coordinates> getRestaurantsStub(Graph<Coordinates> &graph, int nr){
    vector<Coordinates> restaurants;

    srand(nr);

    for (int i = 0; i < nr; ++i) {
        int randV = rand() % graph.getNumVertex();
        Coordinates restaurant = Coordinates(randV);
        restaurants.push_back(restaurant);
    }

    return restaurants;
}

vector<Coordinates> getClientAddressesStub(Graph<Coordinates> &graph, int nr){
    vector<Coordinates> delivery;

    srand(nr * 2);

    for (int i = 0; i < nr; ++i) {
        int randV = rand() % graph.getNumVertex();
        Coordinates address = Coordinates(randV);
        delivery.push_back(address);
    }

    return delivery;
}

vector<Request> getRandomRequests(Graph<Coordinates> &graph, int nr){

    vector<Coordinates> restaurants = getRestaurantsStub(graph, nr);
    vector<Coordinates> clients = getClientAddressesStub(graph, nr);

    vector<Request> requests;
    Date date = Date(2020,5,9);
    Hour hour = Hour(16,44);
    for (int i = 0; i < nr; ++i) {
        hour.setMinute(hour.getMinute()+i);

        vector<Coordinates> checkpoints;
        checkpoints.push_back(restaurants.at(i));
        requests.push_back(Request(i,date,hour,checkpoints, clients.at(i),i+1));
    }

    return requests;
}

void generateRandomGrid(int n, bool random, ostream &nodes, ostream &edges, bool bike){

    // Call this on main:
    //    ofstream nodes , edges;
    //    nodes.open("../Mapas/GridGraphs/20x20/nodes.txt",ios_base::trunc);
    //    edges.open("../Mapas/GridGraphs/20x20/edges.txt",ios_base::trunc);
    //    generateRandomGrid(20, true, nodes, edges);

    int totalNodes = n * n;
    nodes << totalNodes << endl;

    int x = 0;
    int y = 0;

    srand(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            nodes << "(" << j + i * n << ", " << x << ", " << y << ")" << endl;
            if (random)
                y += rand() % 100 + 20;
            else
                y += 50;
        }
        y = 0;
        if (random)
            x += rand() % 100 + 20;
        else
            x += 50;
    }

    cout << "#############" << endl;

    int totalEdges = totalNodes * 2 - n * 2;

    edges << totalEdges << endl;

    for (int k = 0; k < totalNodes; ++k) {

        if (bike && rand() % 4 < 3)
            continue;

        if (k + 1 < totalNodes && (k + 1) % n != 0){
            edges << "(" << k << ", " << k + 1 << ")" << endl;
        }
        if (k + n < totalNodes){
            edges << "(" << k << ", " << k + n << ")" << endl;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Hour &hour) {
    os << hour.hour << ":" << hour.minute;
    return os;
}
