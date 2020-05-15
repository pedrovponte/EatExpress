//
// Created by pedro on 15/05/2020.
//

#include <iostream>
#include <vector>
#include "app.h"
#include "Employee.h"
#include "utils.h"

using namespace std;

vector<Employee*> employees;

int make_request() {

}

int grid4x4() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "4x4", true);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(13),20,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(4),40,MOTORCYCLE,true);
    employees.push_back(employee2);

    return 0;
}

int grid8x8() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(69),20,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(38),40,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(3),25,BIKE,true);
    employees.push_back(employee3);

    return 0;
}

int grid16x16() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "16x16Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    
}

int grid20x20() {

}

int grid30x30() {

}

int grid50x50() {

}

int chooseMap() {
    char opt;

    cout << "\tWelcome to UghEats. Please select the map that you want to use: " << endl
        << "\t--------------------------------------------------------------------" << endl
        << endl
        << "\t(A) GridGraph 4x4" << endl
        << "\t(B) GridGraph 8x8" << endl
        << "\t(C) GridGraph 16x16" << endl
        << "\t(D) GridGraph 20x20" << endl
        << "\t(E) GridGraph 30x30" << endl
        << "\t(F) GridGraph 50x50" << endl
        << "\t(X) Exit" << endl
        << endl
        << "\t------------------------------------" << endl
        << "\tYour option (letter): ";

    cin >> opt;
    cin.ignore(1000, '\n');

    switch (opt) {
        case 'A':
            system("CLS");
            grid4x4();
            break;
        case 'B':
            system("CLS");
            grid8x8();
            break;
        case 'C':
            system("CLS");
            grid16x16();
            break;
        case 'D':
            system("CLS");
            grid20x20();
            break;
        case 'E':
            system("CLS");
            grid30x30();
            break;
        case 'F':
            system("CLS");
            grid50x50();
            break;
        case 'X':
            return 1;
        default:
            system("CLS");
            break;
    }

    return 0;
}
