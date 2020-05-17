//
// Created by pedro on 15/05/2020.
//

#include <iostream>
#include <vector>
#include <ctime>
#include "app.h"
#include "Task.h"
#include <algorithm>
#include <iomanip>

using namespace std;

vector<Employee*> employees;
map<unsigned long, VertexType> restaurants;
int id = 0;

Request make_request(Graph<Coordinates> graph) {
    unsigned long int opt, client_vertex, rest_vertex;
    int cargo = 0;
    vector<unsigned long> restaurantIds;
    vector<Coordinates> checkpoints;
    Date date;
    Hour hour;

    cout << endl << "\tMake your request: " << endl
        << "\t----------------------" << endl
        << "\tRestaurants: " << endl
        << endl;

    for(auto i : restaurants) {
        restaurantIds.push_back(i.first);
        cout << "\tType: " << restaurantType(i.second) << right << setw(20) << "Vertex id: " << i.first << endl;
    }

    cout << endl << "\t--------------------------------"<<endl;

    char cont;

    do{
        do{
            cout << "\tChoose a restaurant (Vertex number): ";

            cin >> rest_vertex;
            cin.ignore(1000, '\n');
            cout << endl;
        } while(find(restaurantIds.begin(), restaurantIds.end(),rest_vertex) == restaurantIds.end() || find(checkpoints.begin(), checkpoints.end(),Coordinates(rest_vertex)) != checkpoints.end());

        do{
            cout << "\tHow many meals do you desire from this restaurant (1 to 10) ? ";

            cin >> opt;
            cin.ignore(1000, '\n');

            cout << endl;
            if(opt >= 11 || opt < 1) cout << "Try again!" << endl;
        } while(opt >= 11 || opt < 1 || cargo + opt > 10);
        checkpoints.push_back(Coordinates(rest_vertex));

        cargo += opt;
        if(cargo == 10) break;

        cout << "\tDo you want to choose more restaurants? (Y / N) ";
        cin >> cont;
        cin.ignore(1000, '\n');
        cout << endl;

    } while((cont == 'Y' || cont == 'y') && checkpoints.size() < restaurantIds.size());

    do{
        cout << endl
             << "\tInsert your location vertex: ";
        cin >> client_vertex;
        cin.ignore(1000, '\n');
    } while(opt >= graph.getNumVertex());

    time_t t = time(0);
    tm* now = localtime(&t);

    date = Date(now->tm_year + 1900, 1 + now->tm_mon, now->tm_mday);
    hour = Hour(now->tm_hour + 1, now->tm_min);

    Request request = Request(id, date, hour, checkpoints, Coordinates(client_vertex),cargo);

    return request;
}

string restaurantType(VertexType v){
    switch(v) {
        case RESTAURANT:
            return "Restaurant";
        case FAST_FOOD:
            return "Fast Food";
        case VEGETARIAN:
            return "Vegetarian";
        case PIZZA:
            return "Pizzeria";
        default:
            return "Other";
    }
}

int deliveryRequests(Graph<Coordinates> graph, Graph<Coordinates> reducedGraph, Request r) {
    system("CLS");

    if(r.getCheckpoints().size() == 1){
        min_priority_queue requests;
        requests.push(r);
        vector<Task*> t = distributeRequests(graph, reducedGraph,requests,employees);

        for(Task * task : t){
            cout << *task << endl;
            viewSinglePath(graph,task->getPath(),task->getVehicleType());
        }
    }
    else {
        Task *t = multipleRestaurantsRequest(graph, reducedGraph, employees, r);

        vector<Task *> tasks;
        tasks.push_back(t);

        for(Task * task : tasks) {
            cout << *task << endl;
            if (task->getVehicleType() == CAR || task->getVehicleType() == MOTORCYCLE)
                viewEmployeePath(graph, tasks);
            else if (task->getVehicleType() == BIKE || task->getVehicleType() == FOOT)
                viewEmployeePath(graph, tasks);
        }
    }
    return 0;
}

int grid4x4() {

    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "4x4", true, preview);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(13),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(4),5,MOTORCYCLE,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2, Coordinates(16), 10, CAR, true);
    employees.push_back(employee3);

    restaurants = graph.getVTypes();

    Request r = make_request(graph);

    deliveryRequests(graph, graph, r);

    return 0;
}

int grid8x8() {
    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "8x8", true, preview);
    graph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(69),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(38),10,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(3),2,BIKE,true);
    employees.push_back(employee3);

    restaurants = graph.getVTypes();

    Request r = make_request(graph);

    deliveryRequests(graph, graph, r);

    return 0;
}

int grid16x16() {
    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16Random", true, preview);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "16x16Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    Employee * employee1 = new Employee(0,Coordinates(182),1,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(155),10,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(37),5,MOTORCYCLE,true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3,Coordinates(193),2,BIKE,true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4,Coordinates(45),10,CAR,true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5,Coordinates(232),5,MOTORCYCLE,true);
    employees.push_back(employee6);
    Employee * employee7 = new Employee(6,Coordinates(115),1,FOOT,true);
    employees.push_back(employee7);

    restaurants = graph.getVTypes();

    Request r = make_request(graph);

    deliveryRequests(graph, reducedGraph, r);

    return 0;
}

int grid20x20() {
    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "20x20", true, preview);
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

    Request r = make_request(graph);

    deliveryRequests(graph, reducedGraph, r);

    return 0;
}

int grid30x30() {
    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "30x30", true, preview);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "30x30Bike", true);

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

    Request r = make_request(graph);

    deliveryRequests(graph, reducedGraph, r);

    return 0;
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

bool previewCity(){
    char opt;
    cout << "\tWould you like to preview the city? (Y / N) ";
    cin >> opt;
    cin.ignore(1000, '\n');

    return opt == 'Y' || opt == 'y';
}
