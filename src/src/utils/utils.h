//
// Created by diana on 06/05/20.
//

#ifndef CAL_T3G4_UTILS_H
#define CAL_T3G4_UTILS_H

#include "../graph/Graph.h"
#include "../eatExpress/Employee.h"
#include <graphviewer.h>
#include <string>
#include <map>

class SingleTask;
class SpecialTask;
class Request;

using namespace std;

// Date and Hour Classes

class Hour {
    int hour;
    int minute;

public:

    Hour(int hour = -1, int minute = -1) : hour(hour), minute(minute) {};

    Hour(const Hour & h){
        this->minute = h.getMinute();
        this->hour = h.getHour();
    }

    int getHour() const {
        return hour;
    }

    void setHour(int hour) {
        Hour::hour = hour;
    }

    int getMinute() const {
        return minute;
    }

    void setMinute(int minute) {
        Hour::minute = minute;
    }

    bool operator <(const Hour & h) const{
        if(hour == h.getHour()) return this->minute < h.getMinute();
        else return hour < h.getHour();
    }

    friend std::ostream &operator<<(std::ostream &os, const Hour &hour);
};

class Date {

    int year, month, day;

public:
    Date(int year = -1, int month = -1, int day = -1) : year(year), month(month), day(day) {};

    Date(const Date & d){
        this->year = d.getYear();
        this->day = d.getDay();
        this->month = d.getMonth();
    }

    bool operator==(const Date &rhs) const {
        return year == rhs.year &&
               month == rhs.month &&
               day == rhs.day;
    }

    int getYear() const {
        return year;
    }


    int getMonth() const {
        return month;
    }


    int getDay() const {
        return day;
    }


    bool operator <(const Date & d) const{
        if(year == d.getYear()){
            if(month == d.getMonth())
                return day < d.getDay();
            return month < d.getMonth();
        }
        return year<d.getYear();
    }

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
};

// Distances

double euclideanDistance(double x1, double y1, double x2, double y2);

double haversineDistance(double lat1, double long1, double lat2, double long2);

// Load Graphs and Tags

Graph<Coordinates> loadGraph(string folder, string subFolder, bool euclidean, bool preview = false);

map<unsigned long, VertexType> loadTags(string path);

void cleanGraph(Graph<Coordinates> &graph);

// Graphic Viewer

void viewSinglePath(const Graph<Coordinates> & graph, const vector<Coordinates> & path, VehicleType type = CAR);

void viewEmployeePath(const Graph<Coordinates> & graph, vector<SingleTask*> tasks);

void viewSpecialTask(const Graph<Coordinates> & graph, SpecialTask * task);

void viewEmployeesPaths(const Graph<Coordinates> & graph,const Graph<Coordinates> & reducedGraph, vector<SingleTask*> tasks);

void graphViewerProperties(GraphViewer * gv);

void setRestaurantIcon(GraphViewer * gv, VertexType type, unsigned long id);

void setVehicleIcon(GraphViewer * gv, VehicleType type, unsigned long id);

void drawGraph(GraphViewer *gv, const Graph<Coordinates> & graph);

// Stubs and utils for test functions

vector<Coordinates> getRestaurantsStub(Graph<Coordinates> &graph, int nr);

vector<Coordinates> getClientAddressesStub(Graph<Coordinates> &graph, int nr);

vector<Request> getRandomRequests(Graph<Coordinates> &graph, int nr);

void generateRandomGrid(int n, bool random, ostream &nodes, ostream &edges, bool bike);

#endif //CAL_T3G4_UTILS_H
