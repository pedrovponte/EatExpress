//
// Created by pedro on 15/05/2020.
//

#include <iostream>
#include <vector>
#include <ctime>
#include "app.h"
#include "Employee.h"
#include "utils.h"
#include "Request.h"

using namespace std;

vector<Employee*> employees;
map<unsigned long, VertexType> restaurants;
vector<Request> requests;
int id = 0;
char cont = 'Y';

int make_request(Graph<Coordinates> graph, Graph<Coordinates> reducedGraph) {
    int opt;
    int client_vertex;
    int cargo;
    Date date;
    Hour hour;

    cout << "\tMake your request: " << endl
        << "\t----------------------" << endl
        << "\tRestaurants: " << endl
        << endl;

    for(auto i : restaurants) {
        cout << "\tType: " << i.second << "\tVertex id: " << i.first << endl;
    }

    cout << endl << "\t--------------------------------" << endl
        << "\tChoose a restaurant (Vertex number): ";
    cin >> opt;
    cin.ignore(1000, '\n');
    cargo++;

    vector<Coordinates> checkpoints;
    checkpoints.push_back(Coordinates(opt));

    while((cont == 'Y' || cont == 'y' ) && cargo < 11)  {
        cout << endl << "\tDo you want to chose more restaurants? (Y / N) ";
        cin >> cont;
        cin.ignore(1000, '\n');
        if (cont == 'Y' || cont == 'y') {
            cout << "Choose a restaurant (Vertex number): ";
            cin >> opt;
            cin.ignore(1000, '\n');
            checkpoints.push_back(Coordinates(opt));
            cargo++;
        }
        else
            break;
    }

    cout << endl
        << "\tInsert your location vertex: ";
    cin >> client_vertex;
    cin.ignore(1000, '\n');

    time_t t = time(0);
    tm* now = localtime(&t);

    date = Date(now->tm_year + 1900, 1 + now->tm_mon, now->tm_mday);
    hour = Hour(now->tm_hour + 1, now->tm_min);

    requests.push_back(Request(id, date, hour, checkpoints, client_vertex, cargo));

    return 0;
}

void grid4x4() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "4x4", true);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(13),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(4),5,MOTORCYCLE,true);
    employees.push_back(employee2);

    restaurants = graph.getVTypes();

    make_request(graph, graph);
}

void grid8x8() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(69),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(38),10,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(3),2,BIKE,true);
    employees.push_back(employee3);

    restaurants = graph.getVTypes();

    make_request(graph, graph);
}

void grid16x16() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "16x16Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(203),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(155),10,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(37),5,MOTORCYCLE,true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3,Coordinates(193),2,BIKE,true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4,Coordinates(45),10,CAR,true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5,Coordinates(288),5,MOTORCYCLE,true);
    employees.push_back(employee6);

    restaurants = graph.getVTypes();

    make_request(graph, reducedGraph);
}

void grid20x20() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "20x20", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "20x20Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0, Coordinates(90), 1, FOOT, true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1, Coordinates(263), 2, BIKE, true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2, Coordinates(333), 2, BIKE, true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3, Coordinates(45), 1, FOOT, true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4, Coordinates(353), 10, CAR, true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5, Coordinates(342), 5, MOTORCYCLE, true);
    employees.push_back(employee6);
    Employee * employee7 = new Employee(6, Coordinates(96), 10, CAR, true);
    employees.push_back(employee7);
    Employee * employee8 = new Employee(7, Coordinates(167), 5, MOTORCYCLE, true);
    employees.push_back(employee8);
    Employee * employee9 = new Employee(8, Coordinates(271), 10, CAR, true);
    employees.push_back(employee9);

    restaurants = graph.getVTypes();

    make_request(graph, reducedGraph);
}

void grid30x30() {
    Graph<Coordinates> graph = loadGraph("GridGraphs", "20x20", true);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "20x20Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0, Coordinates(50), 1, FOOT, true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1, Coordinates(229), 2, BIKE, true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2, Coordinates(69), 2, BIKE, true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3, Coordinates(452), 1, FOOT, true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4, Coordinates(362), 2, BIKE, true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5, Coordinates(146), 2, BIKE, true);
    employees.push_back(employee6);
    Employee * employee7 = new Employee(6, Coordinates(165), 10, CAR, true);
    employees.push_back(employee7);
    Employee * employee8 = new Employee(7, Coordinates(94), 5, MOTORCYCLE, true);
    employees.push_back(employee8);
    Employee * employee9 = new Employee(8, Coordinates(304), 5, MOTORCYCLE, true);
    employees.push_back(employee9);
    Employee * employee10 = new Employee(9, Coordinates(546), 10, CAR, true);
    employees.push_back(employee10);
    Employee * employee11 = new Employee(10, Coordinates(636), 10, CAR, true);
    employees.push_back(employee11);
    Employee * employee12 = new Employee(11, Coordinates(761), 5, MOTORCYCLE, true);
    employees.push_back(employee12);
    Employee * employee13 = new Employee(12, Coordinates(620), 10, CAR, true);
    employees.push_back(employee13);
    Employee * employee14 = new Employee(13, Coordinates(749), 10, CAR, true);
    employees.push_back(employee14);

    restaurants = graph.getVTypes();

    make_request(graph, reducedGraph);
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
        case 'X':
            return 1;
        default:
            system("CLS");
            break;
    }

    return 0;
}
