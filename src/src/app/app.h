//
// Created by pedro on 15/05/2020.
//

#ifndef CAL_T3G4_APP_H
#define CAL_T3G4_APP_H

#include "../eatExpress/Coordinates.h"
#include "../graph/Graph.h"
#include "../eatExpress/Request.h"
#include "../eatExpress/SpecialTask.h"

/*
 * Allow the user to make a Request by choosing one or multiple meals from the restaurants available in the graph he previously selected.
 * The user must also give a valid delivery address for the Request (the id of an existing Vertex).
 */
Request makeRequest(Graph<Coordinates> & graph);

/*
 * An employee from the available employees will be assigned to complete the Request. The choice is made according to the number of restaurants chosen:
 * - If the Request has only one restaurant, the employee is chosen based on its distance, capacity and type of vehicle used.
 * - If the Request includes multiple restaurants, the employee chosen is the one that, having capacity to complete the request, matches
 * the shortest path to go through all the restaurants (always visiting the restaurant closer to its previous position).
 * Shows the path traveled by the Employee(Graph Viewer), the total distance and the estimated delivery time.
 */
int deliveryRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, Request & r);

int grid4x4();
int grid8x8();
int grid16x16();
int grid20x20();
int grid30x30();
int penafiel();

int chooseMap();

int simulationMenu(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph);

/*
 * Simulate the case where there is only one Employee that must fulfill several Requests in one displacement.
 * Generates 1 to 5 - the number is chosen by the user; random Requests to be completed by the same Employee.
 * Calculates the best Route to pick and deliver the requests (TSP variant) and shows the order in which the checkpoints are visited
 * ,the final path (GraphViewer), the distances and the estimated delivery time for each Request.
 */
int simultaneousRequestsSimulation(Graph<Coordinates> & graph);

/*
 * Simulate the case where the Requests are assigned  on a first-come, first-served basis to an Employee, which completes one Request at a time.
 * Lets the user choose between 1 a 10 Employees and 1 to 15 Requests.
 * Generates the number of Requests and Employees determined by the user, using valid Ids for Penafiel's Graph.
 * Distributes the Requests among the Employees, based on their vehicles, distances to the restaurants, capacity and availability.
 * Allows the user to visualize the total path of the Employee, the total paths of all the Employees or the path to complete a specific Request.
 */
int temporalOrderRequestsSimulation(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph);

/*
 * Simulate the case where the Requests are assigned  on a first-come, first-served basis to an Employee, which completes one Request at a time.
 * Lets the user choose between 1 a 10 Employees and 1 to 15 Requests.
 * Randomly generates the number of Requests and Employees determined by the user.
 * Distributes the Requests among the Employees, based on their vehicles, distances to the restaurants, capacity and availability.
 * Allows the user to visualize the total path of the Employee, the total paths of all the Employees or the path to complete a specific Request.
 */
int simulationMenuPenafiel(Graph<Coordinates> & graph);

/*
 * Simulate the case where there is only one Employee that must fulfill several Requests in one displacement.
 * Generates 1 to 5 - the number is chosen by the user; random Requests to be completed by the same Employee.
 * Calculates the best Route to pick and deliver the requests (TSP variant) and shows the order in which the checkpoints are visited
 * ,the final path (Graph Viewer), the distances and the estimated delivery time for each Request.
 */
int simultaneousRequestsSimulationPenafiel(Graph<Coordinates> & graph);

/*
 * Simulate the case where the Requests are assigned  on a first-come, first-served basis to an Employee, which completes one Request at a time.
 * Lets the user choose between 1 a 10 Employees and 1 to 15 Requests.
 * Generates the number of Requests and Employees determined by the user, using valid Ids for Penafiel's Graph.
 * Distributes the Requests among the Employees, based on their vehicles, distances to the restaurants, capacity and availability.
 * Allows the user to visualize the total path of the Employee, the total paths of all the Employees or the path to complete a specific Request.
 */
int temporalOrderRequestsSimulationPenafiel(Graph<Coordinates> & graph);
vector<Request> requestsPenafiel(int number);
vector<Employee*>  employeesPenafiel(int number);

min_priority_queue randomRequests1(unsigned number, unsigned vertices);
vector<Request> randomRequests2(unsigned number, unsigned vertices);
vector<Employee*> randomEmployees(unsigned number, unsigned vertices);
Employee * getRandomEmployee(unsigned vertices);

string restaurantType(VertexType v);

char singleRequest();
bool previewCity();

#endif //CAL_T3G4_APP_H
