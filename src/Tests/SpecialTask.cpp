//
// Created by Diana Freitas on 19/05/2020.
//

#include "SpecialTask.h"

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member
void repeatedRestaurants(vector<Request> & to_pick, vector<Request> & to_deliver);

vector<Request> orderByRestaurantDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin);

vector<Request> orderByDeliveryDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin);

vector<Coordinates> simultaneousRequests(Graph<Coordinates> & graph,vector<Request> & requests, Employee* employee);

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member

vector<Request> orderByRestaurantDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin){
    vector<Request> result;
    int iter = requests.size();
    int orig = graph.findVertexIdx(origin);
    int choice;
    double bestDist;

    for(int i = 0; i < iter; i++){
        // Get nearest restaurant
        bestDist = INF;
        for(int j = 0; j < requests.size(); j++){
            double restaurant_dist = graph.getDist(orig,graph.findVertexIdx(requests[j].getCheckpoints()[0]));
            if(restaurant_dist < bestDist){
                choice = j;
                bestDist = restaurant_dist;
            }
        }
        result.push_back(requests[choice]);
        orig = graph.findVertexIdx(requests[choice].getCheckpoints()[0]);
        requests.erase(requests.begin() + choice);
    }

    return result;
}

vector<Request> orderByDeliveryDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin){
    vector<Request> result;
    int iter = requests.size();
    int orig = graph.findVertexIdx(origin);
    int choice;
    double bestDist;

    for(int i = 0; i < iter; i++){
        // Get nearest restaurant
        bestDist = INF;
        for(int j = 0; j < requests.size(); j++){
            double restaurant_dist = graph.getDist(orig,graph.findVertexIdx(requests[j].getDeliveryAddr()));
            if(restaurant_dist < bestDist){
                choice = j;
                bestDist = restaurant_dist;
            }
        }
        result.push_back(requests[choice]);
        orig = graph.findVertexIdx(requests[choice].getDeliveryAddr());
        requests.erase(requests.begin() + choice);
    }

    return result;
}

void repeatedRestaurants(vector<Request> & to_pick, vector<Request> & to_deliver){
    vector<Request>::iterator it = to_pick.begin() + 1;
    while(it != to_pick.end()){
        // If there is another request with the same restaurant then pick both
        if(it->getCheckpoints()[0] == to_pick.front().getCheckpoints()[0]){
            to_deliver.push_back(*it);
            it = to_pick.erase(it);
        }
        else it++;
    }
}

vector<Coordinates> simultaneousRequests(Graph<Coordinates> & graph,vector<Request> & requests, Employee* employee){
    Coordinates origin = employee->getCoordinates();
    vector<Request> to_pick = orderByRestaurantDistance(graph, requests, origin);
    vector<Request> to_deliver;
    vector<Coordinates> path;
    int totalCargo = 0;

    int iter = 0;
    while(!to_deliver.empty() || !to_pick.empty()){
        if(iter == 0 || to_deliver.empty()){
            cout << iter << endl;
            // Go pick from restaurant
            origin = to_pick.front().getCheckpoints()[0];
            path.push_back(origin);
            totalCargo += to_pick.front().getCargo();

            repeatedRestaurants(to_pick,to_deliver);
            to_deliver.push_back(to_pick.front());
            to_pick.erase(to_pick.begin());
        }
        else if(totalCargo == employee->getMaxCargo() || to_pick.empty()){
            // Delivers one request
            origin = to_deliver.front().getDeliveryAddr();
            path.push_back(origin);
            to_deliver.erase(to_deliver.begin());
        }
        else{
            // Delivers one request or picks it from the restaurant -> nearest point
            int nearest_address = graph.findVertexIdx(to_deliver.front().getDeliveryAddr());
            int nearest_restaurant = graph.findVertexIdx(to_pick.front().getCheckpoints()[0]);

            if(graph.getDist(graph.findVertexIdx(origin),nearest_address) < graph.getDist(graph.findVertexIdx(origin),nearest_restaurant)){
                // Delivers one request
                origin = to_deliver.front().getDeliveryAddr();
                path.push_back(origin);
                to_deliver.erase(to_deliver.begin());
            }
            else{
                // Go pick from restaurant
                origin = to_pick.front().getCheckpoints()[0];
                path.push_back(origin);
                totalCargo += to_pick.front().getCargo();

                repeatedRestaurants(to_pick,to_deliver);

                to_deliver.push_back(to_pick.front());
                to_pick.erase(to_pick.begin());
            }
        }

        to_deliver = orderByDeliveryDistance(graph,to_deliver,origin);
        to_pick = orderByRestaurantDistance(graph,to_pick,origin);

        iter++;
    }

    return path;
}
