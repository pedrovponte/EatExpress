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
    map<unsigned long, int> times; // Match each Request id with the estimated time of the Request
    vector<Coordinates> mainCheckpoints;
public:
    SpecialTask(Employee * employee, const vector<Request> & requests, int id);

    /*
     * Build the complete path to go through all the checkpoints - restaurants and delivery addresses; in order.
     * Saves the main checkpoints of the path and the estimated times for each Request.
     * The order of visit of the checkpoints must be already defined when this function is used.
     * Uses graph's distance matrix, pre-processed with Floyd Warshall.
     */
    virtual void setFloydWarshallPath(Graph<Coordinates> & graph, const vector<pair<Coordinates,unsigned long>> & checkpoints);
    vector<Coordinates> getDeliveryAddresses() const;
    int findRequestId(unsigned long id);
    friend std::ostream &operator<<(std::ostream &os, const SpecialTask &task);
};

/**************** One Employee - Best Route to pick and deliver multiple requests (TSP variant) ***************/

/*
 * Whenever a Request is picked from a restaurant, pick all possible Requests from the same restaurant, never exceeding Employee's capacity.
 */
void repeatedRestaurants(vector<Request> & to_pick, vector<Request> & to_deliver, int & totalCargo, const int maxCargo);

/*
 * Places the Request corresponding to the nearest restaurant at the begging of the Requests vector
 */
void setNearestRestaurant(Graph<Coordinates> & graph, vector<Request> & requests, Coordinates origin);

/*
 * Places the Request corresponding to the nearest delivery address at the begging of the Requests vector
 */
void setNearestDeliveryAddress(Graph<Coordinates> & graph, vector<Request> & requests, Coordinates origin);

/*
 * Takes one Employee and a set of Requests and determines a path to complete all the Requests.
 * To choose the next checkpoint to visit, the algorithm:
 * - starts by choosing the nearest restaurant to the employee - first iteration;
 * - takes into account that a restaurant from one Request must always be visited before its delivery address.
 * - picks the checkpoint that is closer to the previous checkpoint visited, whenever possible.
 * - always chooses to deliver a request that was already picked from the restaurant when the capacity of the Employee doesn't allow any more cargo.
 * - avoids going to the same restaurant multiple times if the capacity is enough to take more than one request from that restaurant.
 *
 * @param graph the graph used for cars and motorcycles
 * @param requests the requests
 * @param employee the employee
 * @return a task that assigns the requests to the employee
 */
SpecialTask * simultaneousRequests(Graph<Coordinates> & graph, vector<Request> & requests, Employee* employee);

#endif //CAL_T3G4_SPECIALTASK_H
