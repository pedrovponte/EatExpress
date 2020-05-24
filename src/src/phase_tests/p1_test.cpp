//
// Created by edurbrito on 09/05/20.
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

TEST(CAL_T3G4, test_dijkstra_time_ph1){

    vector<vector<int>> output;

    Graph<Coordinates> graph = loadGraph("GridGraphs", "30x30", true);

    Employee employee(0,Coordinates(10),1000,CAR,true);

    // srand(time(NULL));

    for (int j = 0; j < 100; ++j) {
        vector<int> v;
        output.push_back(v);

        // int nRequests = rand() % 50 + 1;

        vector<Request> requests = getRandomRequests(graph,100);

        // Start counting time
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; ++i) {
            SingleTask task = SingleTask(&employee, requests.at(i), i);
            task.setDijkstraPath(graph); // Executes Dijkstra algorithm from the employee to the restaurant and then from that to the client's house
            auto checkpoint = std::chrono::high_resolution_clock::now();

            auto elapsed = chrono::duration_cast<chrono::microseconds>(checkpoint - start).count();
            output.at(j).push_back(elapsed);
        }

        // End counting time
    }

    cout << "OUTPUT FOR GRAPHIC ANALYSIS" << endl;

    for (int k = 0; k < 100; ++k) {
        int mean = 0;
        for (int i = 0; i < 100; ++i) {
            mean += output.at(i).at(k);
        }
        mean = mean/100;
        // cout << "FOR n = " <<  k + 1 << " requests Dijkstra run on " << mean << " micro-seconds" << endl;
        cout << k + 1 << "," << mean << endl;
    }

}

TEST(CAL_T3G4, test_floyd_wharshall_time_ph1){

    vector<vector<int>> output;

    bool preprocessed = false;

    Graph<Coordinates> graph = loadGraph("GridGraphs", "30x30", true);

    Employee employee(0,Coordinates(10),1000,CAR,true);

    // srand(time(NULL));

    for (int j = 0; j < 100; ++j) {
        vector<int> v;
        output.push_back(v);

        // int nRequests = rand() % 50 + 1;

        vector<Request> requests = getRandomRequests(graph,100);

        // Start counting time
        auto start = std::chrono::high_resolution_clock::now();

        if (!preprocessed){
            graph.floydWarshallShortestPath(); // Pre-processing
            preprocessed = !preprocessed;
        }

        for (int i = 0; i < 100; ++i) {
            SingleTask task = SingleTask(&employee, requests.at(i), i);
            task.setFloydWarshallPath(graph); // Executes Floyd-Wharshall algorithm from the employee to the restaurant and then from that to the client's house

            auto checkpoint = std::chrono::high_resolution_clock::now();

            auto elapsed = chrono::duration_cast<chrono::microseconds>(checkpoint - start).count();
            output.at(j).push_back(elapsed);
        }

    }

    cout << "OUTPUT FOR GRAPHIC ANALYSIS" << endl;

    for (int k = 0; k < 100; ++k) {
        int mean = 0;
        for (int i = 0; i < 100; ++i) {
            mean += output.at(i).at(k);
        }
        mean = mean/100;
        // cout << "FOR n = " <<  k + 1 << " requests Dijkstra run on " << mean << " micro-seconds" << endl;
        cout << k + 1 << "," << mean << endl;
    }

}