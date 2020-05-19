//
// Created by Diana Freitas on 19/05/2020.
//

#include "SpecialTask.h"

SpecialTask::SpecialTask(Employee * employee, const vector<Request> & requests, int id) : Task(employee,id), requests(requests) {}

void SpecialTask::setFloydWarshallPath(Graph<Coordinates> & graph, const vector<pair<Coordinates,unsigned long>> & checkpoints){
    if(checkpoints.empty()) return;
    Coordinates orig = employee->getCoordinates();
    vector<Coordinates> tempPath;
    totalDistance = 0;

    sort(requests.begin(),requests.end(),requestsById);
    for(int i = 0; i< checkpoints.size(); i++){
        tempPath = graph.getfloydWarshallPath(orig, checkpoints[i].first);
        totalDistance += graph.getDist(graph.findVertexIdx(orig), graph.findVertexIdx(checkpoints[i].first));

        if(checkpoints[i].first == requests[checkpoints[i].second].getDeliveryAddr()){
            int t = (totalDistance * 60) / (1000 * employee->getAvgVelocity());
            times.insert(make_pair(checkpoints[i].second,t));
            employee->addTime(t);
        }

        if(i == 0) path = tempPath;
        else path.insert(path.end(),tempPath.begin()+1, tempPath.end());
        orig = checkpoints[i].first;
    }

    employee->setCoordinates(path.at(path.size()-1));
    employee->setReady(true);
}

vector<Coordinates> SpecialTask::getDeliveryAddresses() const{
    vector<Coordinates> addresses;
    for(Request r: requests){
        addresses.push_back(r.getDeliveryAddr());
    }
    return addresses;
}

std::ostream &operator<<(std::ostream &os, const SpecialTask &task){
    if(task.employee == nullptr){
        os << "\tRequests couldn't be completed!"<< endl;
        return os;
    }

    os << "\t" << *task.employee<< endl;

    if(!task.path.empty())
        os << "\tInitial Employee's Position: " << task.path[0] << endl;

    os << "\tPath: ";
    for(unsigned int i = 0; i < task.path.size(); i++)
        os << task.path[i] << " ";
    os << endl;

    cout << endl << "\tRequests: "<<endl;
    for(Request r: task.requests){
        cout << "\t" << r << "\tEstimated Time: " << task.times.find(r.getId())->second << " min"<< endl;
    }

    os << endl<< "\tTotal distance: " << task.totalDistance << " m" << endl;

    return os;
}

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member

void setNearestRestaurant(Graph<Coordinates> & graph, vector<Request>  & requests, Coordinates origin){

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

void setNearestDeliveryAddress(Graph<Coordinates> & graph, vector<Request>  & requests, Coordinates origin){

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

void repeatedRestaurants(vector<Request> & to_pick, vector<Request>  & to_deliver, int & totalCargo, const int maxCargo){
    vector<Request>::iterator it = to_pick.begin() + 1;
    while(it != to_pick.end()){
        // If there is another request with the same restaurant then pick both
        if(it->getCheckpoints()[0] == to_pick.front().getCheckpoints()[0] && totalCargo + it->getCargo() <= maxCargo){
            to_deliver.push_back(*it);
            totalCargo += it->getCargo();
            it = to_pick.erase(it);
        }
        else it++;
    }
}

SpecialTask * simultaneousRequests(Graph<Coordinates> & graph, vector<Request> & requests, Employee* employee){
    vector<pair<Coordinates,unsigned long>> path;
    Coordinates origin = employee->getCoordinates();
    vector<Request> to_pick = requests;
    setNearestRestaurant(graph, to_pick, origin);

    vector<Request> to_deliver;

    int iter = 0;
    int totalCargo = 0;
    while(!to_deliver.empty() || !to_pick.empty()){
        // No more requests to pick / No more capacity -> must deliver a request
        if(totalCargo == employee->getMaxCargo() || to_pick.empty()){
            // Deliver one request
            origin = to_deliver.front().getDeliveryAddr();
            path.push_back(make_pair (origin,to_deliver.front().getId()));
            totalCargo -= to_deliver.front().getCargo();

            // Remove from delivery queue
            to_deliver.erase(to_deliver.begin());
        }

        // If it is the first displacement -> pick a request from a restaurant
        // If there are no more requests ready to deliver -> pick a request from restaurant
        else if(iter == 0 || to_deliver.empty()){
            // Go pick from restaurant
            origin = to_pick.front().getCheckpoints()[0];
            path.push_back(make_pair (origin,to_pick.front().getId()));
            totalCargo += to_pick.front().getCargo();

            // Check if there are more requests from the same restaurant
            repeatedRestaurants(to_pick,to_deliver,totalCargo, employee->getMaxCargo());

            // Move request from "to pick" queue to "to deliver" queue
            to_deliver.push_back(to_pick.front());
            to_pick.erase(to_pick.begin());
        }

        // No more requests to pick -> must deliver the remaining requests
        else{

            // Delivers one request or picks it from the restaurant -> nearest point
            int nearest_address = graph.findVertexIdx(to_deliver.front().getDeliveryAddr());
            int nearest_restaurant = graph.findVertexIdx(to_pick.front().getCheckpoints()[0]);

            // If cargo is not available to pick a request or the nearest point is an address
            if(totalCargo + to_pick.front().getCargo() > employee->getMaxCargo() ||
                    graph.getDist(graph.findVertexIdx(origin),nearest_address) < graph.getDist(graph.findVertexIdx(origin),nearest_restaurant)){
                // Delivers one request
                origin = to_deliver.front().getDeliveryAddr();
                path.push_back(make_pair (origin,to_deliver.front().getId()));
                totalCargo -= to_deliver.front().getCargo();

                // Remove from delivery queue
                to_deliver.erase(to_deliver.begin());
            }
            // If the nearest point is a restaurant
            else{
                // Go pick from restaurant
                origin = to_pick.front().getCheckpoints()[0];
                path.push_back(make_pair (origin,to_pick.front().getId()));
                totalCargo += to_pick.front().getCargo();

                // Check if there are more requests from the same restaurant
                repeatedRestaurants(to_pick,to_deliver,totalCargo, employee->getMaxCargo());

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
