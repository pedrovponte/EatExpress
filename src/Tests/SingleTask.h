//
// Created by diana on 09/05/20.
//

#ifndef CAL_T3G4_SINGLETASK_H
#define CAL_T3G4_SINGLETASK_H

#include "Employee.h"
#include "Request.h"
#include "Task.h"

class Request;

class SingleTask : public Task{
    Request request;
    int time;
public:
    SingleTask(Employee *employee, Request request, int id);

    /*
     * Gets the shortest path to go from the Employee's current position to the restaurant and from the restaurant to the delivery address.
     * Uses graph's distance matrix, pre-processed with Floyd Warshall.
     */
    virtual void setFloydWarshallPath(Graph<Coordinates> & graph);
    void setDijkstraPath(Graph<Coordinates> & graph);
    bool isCheckpoint(Coordinates coordinates);
    bool isDeliveryAddress(Coordinates coordinates);
    const Request & getRequest() const;
    int getTime() const;
    bool operator <(const SingleTask & task);
    string pathToString();
    friend std::ostream &operator<<(std::ostream &os, const SingleTask &task);
};

bool compareTasks(SingleTask * t1, SingleTask * t2);

/**************** Distribute Requests among Employees - Phase 2  ***************/

vector<SingleTask*> distributeRequestsByCloseness_FloydWarshall(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

vector<SingleTask*> distributeRequestsByCloseness_Dijkstra(Graph<Coordinates> & graph, queue<Request> & requests, vector<Employee> & employees);

/**************** Distribute Requests among Employees - Phase 3  ***************/

/*
  * Takes two graphs: one for each type of vehicle; and checks if any of the vertices doesn't exist in the graph.
  * If the vertices don't exist in a graph, then the request is not deliverable by the correspondent type of vehicle.
  *
  * @param graph the graph used for cars and motorcycles
  * @param reducedGraph the graph used for bikes and for Employees that travel by foot
  * @param requests the queue of Requests to be analyzed, ordered by date and hour
  * @returns requests of the original queue, now with the deliverable flags set to false if a Request can't be delivered by a type of vehicle
*/
min_priority_queue setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests);

/*
 * Takes two graphs: one for each type of vehicle; and sets the distance between the Employee and the restaurant by checking its pre-processed distance matrix.
 * If any of the vertices doesn't exist in the graph set the request as not deliverable by the correspondent type of vehicle.
 *
 * @param graph the graph used for cars and motorcycles
 * @param reducedGraph the graph used for bikes and for Employees that travel by foot
 * @param employees the employees
 * @param request the request
 */
void setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);

/*
 * Get all the Employees that are suitable to complete a request.
 * An Employee is suitable if:
 *  - the request can be delivered by the vehicle he uses (there is a path for that vehicle to go from the restaurant to the delivery address)
 *  - he has enough capacity to transport the cargo of the request
 *  - he is available (not completing other requests)
 *  - there is a path between its actual position and the restaurant
 *
 * @param employees the employees
 * @param request the request
 * @return the set of employees that are suitable to complete the request
 */
vector<Employee*> getEligibleEmployees(vector<Employee*> & employees, const Request & request);

/*
 * Check if a Request can be delivered by a specific type o vehicle by checking the flags 'deliverableByCar' 'deliverableByFoot' from the Request
 * @param vehicleType the type of vehicle
 * @param request the request
 * @return true if the request can be delivered by thar type of vehicle
 */
bool isDeliverableByVehicle(VehicleType vehicleType, const Request & request);

/*
 * Distribute the Requests according to Phase 3 of the report
 * Taking a queue of Requests ordered by time of arrival and a set of Employees, creates a Task for each Request which matches the Request
 * with the Employee that is most suitable to complete it
 *
 * @see vector<Employee*> getEligibleEmployees(vector<Employee*> & employees, const Request & request)
 * @see bool Employee::operator<(const Employee &rhs)
 *
 * @param graph the graph used for cars and motorcycles
 * @param reducedGraph the graph used for bikes and for Employees that travel by foot
 * @param requests the queue of Requests to be distributed, ordered by date and hour
 * @param employees the employees
 * @returns the tasks that associate each request to an employee
 */
vector<SingleTask*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees);

/**************** Multiple Restaurants Request  ***************/

/* Get all the Employees that are suitable to complete a request.
* An Employee is suitable if:
*  - he has enough capacity to transport the cargo of the request
*  - he is available (not completing other requests)
 *
 * @param employees the employees
 * @param request the request
 * @return the set of employees that are suitable to complete the request
*/
vector<Employee*> getEligibleEmployeesMultipleRestaurants(vector<Employee*> & employees, const Request & request);

/*
 * Get the index of the restaurant which is closer to the previous position
 *
 * @param graph the graph used
 * @param origin the initial position
 * @param restaurants the restaurants
 * @return the index of the restaurant that is closer to the initial position
 */
int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants);

/*
 * Choose the most suitable Employee to complete a Request that includes multiple restaurants:
 * - Calculates, for each eligible Employee, the total distance he must go through to visit every restaurant of the Request and to deliver it.
 * - To calculate the path for each employee, always chooses the nearest restaurant that is not already visited.
 * - Chooses the Employee that matches the shortest distance.
 *
 * @param graph the graph used for cars and motorcycles
 * @param reducedGraph the graph used for bikes and for Employees that travel by foot
 * @param employees the employees
 * @param request the request
 * @return a task that assigns the request to the employee
 */
SingleTask * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request);


#endif //CAL_T3G4_SINGLETASK_H
