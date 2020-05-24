//
// Created by Diana Freitas on 05/05/2020.
//

#ifndef CAL_T3G4_VERTEX_H
#define CAL_T3G4_VERTEX_H

#include <vector>
#include "MutablePriorityQueue.h"
#include "Edge.h"
#include "../eatExpress/Coordinates.h"

using namespace std;

enum VertexType{ OTHER, RESTAURANT, FAST_FOOD, VEGETARIAN, PIZZA};

template <class T>
class Vertex {
    T info;                // contents
    VertexType type;
    vector<Edge<T> > adj;  // outgoing edges
    bool visited;          // auxiliary field
    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    void addEdge(unsigned long id, Vertex<T> *dest, double w);
public:
    Vertex(T in, VertexType type = OTHER);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    VertexType getType() const;
    const vector<Edge<T>> &getAdj() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, VertexType type): info(in), type(type){}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(unsigned long id, Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(id, this, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template<class T>
VertexType Vertex<T>::getType() const {
    return type;
}

#endif //CAL_T3G4_VERTEX_H
