//
// Created by Diana Freitas on 19/05/2020.
//

#ifndef CAL_T3G4_SPECIALTASK_H
#define CAL_T3G4_SPECIALTASK_H


#include "Employee.h"
#include "Request.h"
#include "Task.h"

class SpecialTask : public Task{
    vector<Request> requests;
    //vector<int> times;
public:
    SpecialTask(Employee * employee, vector<Request> & requests, int id);
    virtual void setFloydWarshallPath(Graph<Coordinates> & graph, const vector<Coordinates> & checkpoints);
};

// Simultaneous requests - best route between multiple restaurants and requests for the same staff member
void repeatedRestaurants(vector<Request> & to_pick, vector<Request> & to_deliver);

vector<Request> orderByRestaurantDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin);

vector<Request> orderByDeliveryDistance(Graph<Coordinates> & graph, vector<Request> requests, Coordinates origin);

SpecialTask * simultaneousRequests(Graph<Coordinates> & graph,vector<Request> & requests, Employee* employee);

#endif //CAL_T3G4_SPECIALTASK_H
