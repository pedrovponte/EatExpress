//
// Created by diana on 06/05/20.
//

#ifndef CAL_T3G4_UTILS_H
#define CAL_T3G4_UTILS_H

#include "Graph.h"
#include <graphviewer.h>
#include <string>

class Task;
class Request;

using namespace std;

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
};

double euclideanDistance(double x1, double y1, double x2, double y2);
double haversineDistance(double lat1, double long1, double lat2, double long2);

Graph<Coordinates> loadGraph(string folder, string subFolder, bool euclidean, bool preview = false);

void viewDijkstraShortestPath(const Graph<Coordinates> & graph, const vector<Coordinates> &  path);

void viewFloydWarshallShortestPath(const Graph<Coordinates> & graph, const vector<Coordinates> & path);

void viewMultiplePaths_FloydWarshall(const Graph<Coordinates> & graph, const vector<Task * > tasks);

void graphViewerProperties(GraphViewer * gv);

void drawGraph(GraphViewer *gv, const Graph<Coordinates> & graph);

vector<Coordinates> getRestaurantsStub(Graph<Coordinates> &graph, int nr);

vector<Coordinates> getClientAddressesStub(Graph<Coordinates> &graph, int nr);

vector<Request> getRandomRequests(Graph<Coordinates> &graph, int nr);

void generateRandomGrid(int n, bool random, ostream &nodes, ostream &edges, bool bike);

void cleanGraph(Graph<Coordinates> *graph);

#endif //CAL_T3G4_UTILS_H
