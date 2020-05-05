//
// Created by Diana Freitas on 05/05/2020.
//

#ifndef CAL_T3G4_EDGE_H
#define CAL_T3G4_EDGE_H

template <class T> class Graph;
template <class T> class Vertex;

using namespace std;

template <class T>
class Edge {
    Vertex<T> *orig;
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight

public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
    double getWeight() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}


#endif //CAL_T3G4_EDGE_H
