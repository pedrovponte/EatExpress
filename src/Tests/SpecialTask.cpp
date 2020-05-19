//
// Created by Diana Freitas on 19/05/2020.
//

#include "SpecialTask.h"

SpecialTask::SpecialTask(Employee * employee, vector<Request> & requests, int id) : Task(employee,id), requests(requests) {}

void SpecialTask::setFloydWarshallPath(Graph<Coordinates> & graph, const vector<Coordinates> & checkpoints){
    if(checkpoints.empty()) return;
    vector<Coordinates> tempPath;
    Coordinates orig = checkpoints[0];
    totalDistance = 0;

    for(int i = 1; i< checkpoints.size(); i++){
        tempPath = graph.getfloydWarshallPath(orig, checkpoints[i]);
        totalDistance += graph.getDist(graph.findVertexIdx(orig), graph.findVertexIdx(checkpoints[i]));

        if(i == 1) path = tempPath;
        else path.insert(path.end(),tempPath.begin()+1, tempPath.end());
        orig = checkpoints[i];
    }

    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);

    int t = (totalDistance * 60) / (1000 * employee->getAvgVelocity());
    employee->addTime(t);
}

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member

void setNearestRestaurant(Graph<Coordinates> & graph, requests_queue & requests, Coordinates origin){

    if(requests.empty()) return;

    int orig = graph.findVertexIdx(origin);
    int choice;
    double bestDist = INF;

    // Put nearest restaurant in the top of the queue
    for(int j = 0; j < requests.size(); j++){
        double restaurant_dist = graph.getDist(orig,graph.findVertexIdx(requests[j].getCheckpoints()[0]));
        if(restaurant_dist < bestDist){
            choice = j;
            bestDist = restaurant_dist;
        }
    }
    Request temp = requests[choice];
    requests.erase(requests.begin() + choice);
    requests.insert(requests.begin(),temp);
}

void setNearestDeliveryAddress(Graph<Coordinates> & graph, requests_queue & requests, Coordinates origin){

    if(requests.empty()) return;

    int orig = graph.findVertexIdx(origin);
    int choice;
    double bestDist = INF;

    // Put nearest delivery address in the top of the queue
    for(int j = 0; j < requests.size(); j++){
        double deliveryAddr_dist = graph.getDist(orig,graph.findVertexIdx(requests[j].getDeliveryAddr()));
        if(deliveryAddr_dist < bestDist){
            choice = j;
            bestDist = deliveryAddr_dist;
        }
    }

    Request temp = requests[choice];
    requests.erase(requests.begin() + choice);
    requests.insert(requests.begin(),temp);
}

void repeatedRestaurants(vector<Request> & to_pick, requests_queue & to_deliver){
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

SpecialTask * simultaneousRequests(Graph<Coordinates> & graph, requests_queue & requests, Employee* employee){
    Coordinates origin = employee->getCoordinates();
    requests_queue to_pick = requests;
    setNearestRestaurant(graph, to_pick, origin);

    vector<Request> to_deliver;
    vector<Coordinates> path;
    path.push_back(employee->getCoordinates());

    int iter = 0;
    while(!to_deliver.empty() || !to_pick.empty()){
        // If it is the first displacement -> pick a request from a restaurant
        // If there are no more requests ready to deliver -> pick a request from restaurant
        if(iter == 0 || to_deliver.empty()){
            // Go pick from restaurant
            origin = to_pick.front().getCheckpoints()[0];
            path.push_back(origin);

            // Check if there are more requests from the same restaurant
            repeatedRestaurants(to_pick,to_deliver);

            // Move request from "to pick" queue to "to deliver" queue
            to_deliver.push_back(to_pick.front());
            to_pick.erase(to_pick.begin());
        }
        // No more requests to pick -> must deliver the remaining requests
        else if(to_pick.empty()){
            // Deliver one request
            origin = to_deliver.front().getDeliveryAddr();
            path.push_back(origin);

            // Remove from delivery queue
            to_deliver.erase(to_deliver.begin());
        }
        else{
            // Delivers one request or picks it from the restaurant -> nearest point
            int nearest_address = graph.findVertexIdx(to_deliver.front().getDeliveryAddr());
            int nearest_restaurant = graph.findVertexIdx(to_pick.front().getCheckpoints()[0]);

            // If the nearest point is an address
            if(graph.getDist(graph.findVertexIdx(origin),nearest_address) < graph.getDist(graph.findVertexIdx(origin),nearest_restaurant)){
                // Delivers one request
                origin = to_deliver.front().getDeliveryAddr();
                path.push_back(origin);

                // Remove from delivery queue
                to_deliver.erase(to_deliver.begin());

            }

            // If the nearest point is a restaurant
            else{
                // Go pick from restaurant
                origin = to_pick.front().getCheckpoints()[0];
                path.push_back(origin);

                // Check if there are more requests from the same restaurant
                repeatedRestaurants(to_pick,to_deliver);

                // Move request from "to pick" queue to "to deliver" queue
                to_deliver.push_back(to_pick.front());
                to_pick.erase(to_pick.begin());
            }
        }

        setNearestRestaurant(graph,to_pick,origin);
        setNearestDeliveryAddress(graph,to_deliver,origin);

        iter++;
    }

    SpecialTask * s = new SpecialTask(employee, requests,0);
    s->setFloydWarshallPath(graph,path);
    return s;
}
