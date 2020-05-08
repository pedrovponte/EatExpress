//
// Created by diana on 06/05/20.
//

#ifndef CAL_T3G4_UTILS_H
#define CAL_T3G4_UTILS_H

#include "Graph.h"
#include <graphviewer.h>
#include <string>

using namespace std;

class Hour {

    int hour;
    int minute;

public:

    Hour(int hour = -1, int minute = -1) : hour(hour), minute(minute) {};

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
};

class Date {

    int year, month, day;

public:
    Date(int year = -1, int month = -1, int day = -1) : year(year), month(month), day(day) {};

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        Date::year = year;
    }

    int getMonth() const {
        return month;
    }

    void setMonth(int month) {
        Date::month = month;
    }

    int getDay() const {
        return day;
    }

    void setDay(int day) {
        Date::day = day;
    }

    friend int validDate(int d, int m, int y) {
        if (d < 1 || d > 31) return 1;
        if (m < 1 || m > 12) return 1;
        if (y < 0) return 1;

        return 0;
    }
};

double euclideanDistance(double x1, double y1, double x2, double y2);
double haversineDistance(double lat1, double long1, double lat2, double long2);

Graph<Coordinates> loadGraph(string folder, string subFolder, bool euclidean);
void viewFileGraph(GraphViewer *gv, string dir, string subDir, bool euclidean);

void viewDijkstraShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, Coordinates orig, const Coordinates & dest);

void viewFloydWarshallShortestPath(GraphViewer *gv, Graph<Coordinates> & graph, const Coordinates & orig, const Coordinates & dest);

void graphViewerProperties(GraphViewer * gv);

#endif //CAL_T3G4_UTILS_H
