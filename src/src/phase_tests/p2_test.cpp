//
// Created by edurbrito on 10/05/20.
//

#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "../graph/Graph.h"
#include "../utils/utils.h"
#include "../eatExpress/Employee.h"
#include "../eatExpress/Request.h"
#include "../eatExpress/SingleTask.h"

using namespace std;
using testing::Eq;

long test_dijkstra_time(int nrequests){

    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    // Add Employees
    vector<Employee> employees;
    Employee employee1(0,Coordinates(10),1000,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(20),1000,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(30),1000,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    vector<Request> requests = getRandomRequests(graph,nrequests);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    int requestsRound = 1;

    // No employees to fulfill the requests
    if(employees.empty()) return 0;

    // Start counting time
    auto start = std::chrono::high_resolution_clock::now();

    while(!requestsQueue.empty()){
        vector<SingleTask*> tasks = distributeRequestsByCloseness_Dijkstra(graph, requestsQueue, employees);

        // Couldn't find any Employees to fulfill the remaining requests
        if(tasks.empty())
            return 0;

        // Get requests distribution and paths
        for(int i = 0; i < tasks.size(); i++){
            tasks[i]->setDijkstraPath(graph);
        }
        requestsRound++;
    }
    auto checkpoint = std::chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(checkpoint - start).count();
    cout << "TIME ELAPSED Dijkstra n = " << nrequests << " | " << elapsed << endl;

    return elapsed;
}

TEST(CAL_T3G4, test_dijkstra_time_ph2){
    for (int i = 250; i < 2001; i += 250) {
        test_dijkstra_time(i);
    }
}

long test_floyd_time(int nrequests){
    Graph<Coordinates> graph = loadGraph("GridGraphs", "16x16", true);

    // Add Employees
    vector<Employee> employees;
    Employee employee1(0,Coordinates(10),40,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(20),40,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(30),40,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    vector<Request> requests = getRandomRequests(graph,nrequests);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    int requestsRound = 1;

    // No employees to fulfill the requests
    if(employees.empty()) return 0;

    // Start counting time
    auto start = std::chrono::high_resolution_clock::now();

    // Pre-process Distances with Floyd Warshall
    graph.floydWarshallShortestPath();

    while(!requestsQueue.empty()){
        vector<SingleTask*> tasks = distributeRequestsByCloseness_FloydWarshall(graph, requestsQueue, employees);

        // Couldn't find any Employees to fulfill the remaining requests
        if(tasks.empty())
            return 0;

        // Get requests distribution and paths
        for(int i = 0; i < tasks.size(); i++){
            // TODO - Call this function in a thread to execute all tasks from one round of requests at the same time
            tasks[i]->setFloydWarshallPath(graph);
        }
        requestsRound++;
    }

    auto checkpoint = std::chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(checkpoint - start).count();
    cout << "TIME ELAPSED Floyd n = " << nrequests << " | " << elapsed << endl;

    return elapsed;
}

TEST(CAL_T3G4, test_floyd_wharshall_time_ph2){
    for (int i = 250; i < 2001; i += 250) {
        test_floyd_time(i);
    }
}

TEST(CAL_T3G4, test_both_times_ph2){

    vector<vector<long>> dvalues;
    vector<vector<long>> fvalues;

    int ntimes = 10;

    for (int j = 0; j < ntimes; ++j) {
        vector<long> vd;
        vector<long> vf;

        for (int i = 250; i < 2001; i += 250) {
            vd.push_back(test_dijkstra_time(i));
            vf.push_back(test_floyd_time(i));
        }
        dvalues.push_back(vd);
        fvalues.push_back(vf);
    }

    vector<long> dmeans = {0,0,0,0,0,0,0,0};
    vector<long> fmeans = {0,0,0,0,0,0,0,0};

    for(auto v : dvalues){
        for (int i = 0; i < v.size(); ++i) {
            dmeans.at(i) += v.at(i);
        }
    }

    for (int i = 0; i < dmeans.size(); ++i) {
        dmeans.at(i) /= ntimes;
        cout << "DIJKSTRA FOR n = " << i*250 + 250 << " | mean = " << dmeans.at(i) << endl;
    }

    for(auto v : fvalues){
        for (int i = 0; i < v.size(); ++i) {
            fmeans.at(i) += v.at(i);
        }
    }

    for (int i = 0; i < fmeans.size(); ++i) {
        fmeans.at(i) /= ntimes;
        cout << "FLOYD FOR n = " << i*250 + 250 << " | mean = " << fmeans.at(i) << endl;
    }
}