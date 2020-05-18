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
vector<unsigned long> restaurantIds;
int id = 0;

Request make_request(Graph<Coordinates> & graph) {
    unsigned long int opt, client_vertex, rest_vertex;

    int cargo = 0;
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
    id++;

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

int deliveryRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, Request & r) {
    system("CLS");

    if(r.getCheckpoints().size() == 1){
        min_priority_queue requests;
        requests.push(r);
        vector<Task*> t = distributeRequests(graph, reducedGraph,requests,employees);

        for(Task * task : t){
            cout << *task << endl;
            if(task->getEmployee() != nullptr)
                viewSinglePath(graph,task->getPath(),task->getVehicleType());
        }
    }
    else {
        Task *t = multipleRestaurantsRequest(graph, reducedGraph, employees, r);

        vector<Task *> tasks;
        tasks.push_back(t);

        for(Task * task : tasks) {
            cout << *task << endl;

            if(task->getEmployee() != nullptr){
                if (task->getVehicleType() == CAR || task->getVehicleType() == MOTORCYCLE)
                    viewEmployeePath(graph, tasks);
                else if (task->getVehicleType() == BIKE || task->getVehicleType() == FOOT)
                    viewEmployeePath(graph, tasks);
            }
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

    char c;
    if((c = singleRequest()) != 'A' && c != 'B')
        return 0;

    bool preview = previewCity();

    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16Random", true, preview);
    Graph<Coordinates> reducedGraph = loadGraph("GridGraphs", "16x16Bike", true);

    graph.floydWarshallShortestPath();
    reducedGraph.floydWarshallShortestPath();

    restaurants = graph.getVTypes();

    if(c == 'B'){
        return simulate(graph,reducedGraph);
    }

    Employee * employee1 = new Employee(0,Coordinates(182),3,FOOT,true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1,Coordinates(155),10,CAR,true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2,Coordinates(37),5,MOTORCYCLE,true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3,Coordinates(193),5,BIKE,true);
    employees.push_back(employee4);
    Employee * employee5 = new Employee(4,Coordinates(45),10,CAR,true);
    employees.push_back(employee5);
    Employee * employee6 = new Employee(5,Coordinates(232),5,MOTORCYCLE,true);
    employees.push_back(employee6);
    Employee * employee7 = new Employee(6,Coordinates(115),4,FOOT,true);
    employees.push_back(employee7);

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

    Employee * employee1 = new Employee(0, Coordinates(90), 4, FOOT, true);
    employees.push_back(employee1);
    Employee * employee2 = new Employee(1, Coordinates(263), 3, BIKE, true);
    employees.push_back(employee2);
    Employee * employee3 = new Employee(2, Coordinates(333), 4, BIKE, true);
    employees.push_back(employee3);
    Employee * employee4 = new Employee(3, Coordinates(45), 3, FOOT, true);
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

// Multiple Requests Simulations

int simulate(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph) {
    unsigned requestsNum, employeesNum;
    int maxRequests = 15;

    for(auto i : restaurants)
        restaurantIds.push_back(i.first);

    do{
        cout << "\t Number of employees (1 to 10) ?: ";
        cin >> employeesNum;
        cin.ignore(1000, '\n');
        cout << endl;
        if(employeesNum > 10 || employeesNum < 1) cout << "Try again!" << endl;
    } while(employeesNum > 10 || employeesNum < 1);

    if(employeesNum < 3) maxRequests = min(employeesNum, 3*employeesNum);
    do{
        cout << "\t Number of requests (1 to " << maxRequests << ") ?: ";
        cin >> requestsNum;
        cin.ignore(1000, '\n');
        cout << endl;
        if(requestsNum > maxRequests || requestsNum < 1) cout << "Try again!" << endl;
    } while(requestsNum > maxRequests || requestsNum < 1);

    min_priority_queue requests = randomRequests(requestsNum,graph.getNumVertex());
    min_priority_queue temp = requests;

    cout << "\t Requests: " << endl;
    while(!temp.empty()){
        cout << "\t " << temp.top();
        temp.pop();
    }

    cout << endl << "\t Employees: " << endl;
    vector<Employee*> employeesList = randomEmployees(employeesNum,graph.getNumVertex());

    for(Employee * e: employeesList)
        cout << "\t " << *e << "; Initial Position: " << e->getCoordinates() << endl;

    vector<Task*> tasks = distributeRequests(graph, reducedGraph, requests, employeesList);

    cout << endl << "\t Request distribution: " << endl;

    for(Task * task : tasks){
        cout << task->toString() << endl;
    }

    char opt = ' ';
    do{
        int n = 0;
        if(opt == 'A'){
            do{
                cout << "\t Request's id: "<<endl;
                cin >> n;
            } while(n < 0 || n > requests.size()-1);

            for(Task * t: tasks){
                if(t->getRequest().getId() == n){
                    if(t->getVehicleType() == CAR || t->getVehicleType() == MOTORCYCLE)
                        viewSinglePath(graph,t->getPath(),t->getVehicleType());
                    else if(t->getVehicleType() == BIKE || t->getVehicleType() == FOOT)
                        viewSinglePath(reducedGraph,t->getPath(),t->getVehicleType());
                    else
                        cout << "The request you choose could not be completed by any of the employees!" << endl;
                }
            }

        }
        else if(opt == 'B'){
            do{
                cout << "\t Employee's id: "<<endl;
                cin >> n;
            } while(n < 0 || n > employeesList.size()-1);

            vector<Task*> employeeTasks;
            VehicleType type = employeesList[n]->getType();

            for(Task * t: tasks ){
                if(t->getEmployee()->getId() == n)
                    employeeTasks.push_back(t);
            }

            if(type == CAR || type == MOTORCYCLE)
                viewEmployeePath(graph,employeeTasks);
            else
                viewEmployeePath(reducedGraph,employeeTasks);
        }
        else if(opt == 'C'){
            viewEmployeesPaths(graph,reducedGraph,tasks);
        }

        cout << "\t (A) View a Request in city map."<<endl;
        cout << "\t (B) View an Employee's complete route in city map. "<<endl;
        cout << "\t (C) View all Employees complete routes in city map."<<endl;
        cout << "\t (X) Exit"<<endl;
        cin >> opt;
        cin.ignore(1000, '\n');
        cout << endl;
    } while(opt == 'A' || opt == 'B' || opt == 'C');

    return 0;
}

min_priority_queue randomRequests(unsigned number, unsigned vertices){
    min_priority_queue requests;
    Date date;
    Hour hour;
    srand (1);
    time_t t = time(0);

    for(int i = 0 ; i < number; i++){
        int restaurant =  rand() % restaurantIds.size();
        int delivery_address = rand() % vertices;
        int cargo = rand() % 10 + 1;

        tm* now = localtime(&t);

        date = Date(now->tm_year + 1900, 1 + now->tm_mon, now->tm_mday);
        hour = Hour(now->tm_hour + 1, now->tm_min);

        Request r(i, date, hour, Coordinates(restaurantIds[restaurant]),Coordinates(delivery_address),cargo);
        requests.push(r);
    }

    return requests;
}

vector<Employee*> randomEmployees(unsigned number, unsigned vertices){
   vector<Employee*> employees;
   int id = 0;
   srand (1);

    if(number == 1){
        int randV = rand() % vertices;
        Employee * e = new Employee(id, Coordinates(randV), 11, CAR, true);
        employees.push_back(e);
    }
    else if(number == 2){
        int randV = rand() % vertices;
        Employee * e1 = new Employee(id, Coordinates(randV), 11, MOTORCYCLE, true);
        employees.push_back(e1);
        id++;
        randV = rand() % vertices;
        Employee * e2 = new Employee(id, Coordinates(randV), 11, CAR, true);
        employees.push_back(e2);
    }
    else{
        int byCar = number/2;
        for (int i = 0; i < byCar; i++) {
            int randV = rand() % vertices;
            int cargo = rand() % 11 + 8;
            Employee * e = new Employee(id, Coordinates(randV), cargo, CAR, true);
            employees.push_back(e);
            id++;
        }

        int byMotorcycle = number/4;
        for (int i = 0; i < byMotorcycle; i++) {
            int randV = rand() % vertices;
            int cargo = rand() % 9 + 6;
            Employee * e = new Employee(id, Coordinates(randV), cargo, MOTORCYCLE, true);
            employees.push_back(e);
            id++;
        }

        int rest = number-byCar-byMotorcycle;
        for (int i = 0; i < rest; i++) {
            int randV = rand() % vertices;
            int randVehicle = rand() % 2;
            VehicleType v = randVehicle == 0 ? BIKE : FOOT;
            int cargo = 3 + rand() % (7-3+1);
            Employee * e = new Employee(id, Coordinates(randV), cargo, v, true);
            employees.push_back(e);
            id++;
        }
    }

    return employees;
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

char singleRequest() {
    char opt;
    cout << "\t (A) Make your request"<<endl;
    cout << "\t (B) Multiple requests simulation"<<endl;
    cout << "\t (X) Exit"<<endl;
    cin >> opt;
    cin.ignore(1000, '\n');

    return opt;
}

bool previewCity(){
    char opt;
    cout << "\tWould you like to preview the city? (Y / N) ";
    cin >> opt;
    cin.ignore(1000, '\n');

    return opt == 'Y' || opt == 'y';
}


