//
// Created by edurbrito on 09/05/20.
//

#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "../Graph.h"
#include "../utils.h"
#include "../Employee.h"
#include "../Request.h"
#include "../Task.h"


using namespace std;
using testing::Eq;

vector<Vertex<Coordinates>*> getRestaurantsStub(Graph<Coordinates> &graph, int nr){
    vector<Vertex<Coordinates>*> restaurants;

    srand(nr);

    for (int i = 0; i < nr; ++i) {
        int randV = rand() % graph.getNumVertex();
        Vertex<Coordinates> * restaurant = graph.findVertex(Coordinates(randV));
        restaurants.push_back(restaurant);
    }

    return restaurants;
}

vector<Vertex<Coordinates>*> getClientAddressesStub(Graph<Coordinates> &graph, int nr){
    vector<Vertex<Coordinates>*> delivery;

    srand(nr * 2);

    for (int i = 0; i < nr; ++i) {
        int randV = rand() % graph.getNumVertex();
        Vertex<Coordinates> * address = graph.findVertex(Coordinates(randV));
        delivery.push_back(address);
    }

    return delivery;
}

vector<Request> getRandomRequests(Graph<Coordinates> &graph, int nr){

    vector<Vertex<Coordinates> *> restaurants = getRestaurantsStub(graph, nr);
    vector<Vertex<Coordinates> *> clients = getClientAddressesStub(graph, nr);

    vector<Request> requests;
    Date date = Date(2020,5,9);
    Hour hour = Hour(16,44);
    for (int i = 0; i < nr; ++i) {
        hour.setMinute(hour.getMinute()+i);

        vector<Vertex<Coordinates> *> checkpoints;
        checkpoints.push_back(restaurants.at(i));
        requests.push_back(Request(i,date,hour,checkpoints, clients.at(i),i+1));
    }

    return requests;
}

TEST(CAL_T3G4, test_dijkstra_time){

    vector<vector<int>> output;

    Graph<Coordinates> graph = loadGraph("GridGraphs", "4x4", true);

    Employee employee(0,Coordinates(10),40,'c',true);

    // srand(time(NULL));

    for (int j = 0; j < 100; ++j) {
        vector<int> v;
        output.push_back(v);

        // int nRequests = rand() % 50 + 1;

        vector<Request> requests = getRandomRequests(graph,100);

        // Start counting time
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; ++i) {
            Task task = Task(employee, requests.at(i));
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

TEST(CAL_T3G4, test_floyd_wharshall_time){

    vector<vector<int>> output;

    bool preprocessed = false;

    Graph<Coordinates> graph = loadGraph("GridGraphs", "4x4", true);

    Employee employee(0,Coordinates(10),40,'c',true);

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
            Task task = Task(employee, requests.at(i));
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