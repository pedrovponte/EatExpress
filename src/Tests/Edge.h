//
// Created by Diana Freitas on 05/05/2020.
//

#ifndef CAL_T3G4_EDGE_H
#define CAL_T3G4_EDGE_H

template <class T> class Graph;
template <class T> class Vertex;

using namespace std;

class NullEdgeException{
public:
    explicit NullEdgeException(){};
};

template <class T>
class Edge {
    Vertex<T> *orig;        // origin vertex
    Vertex<T> * dest;       // destination vertex
private:

    double weight;         // edge weight
    unsigned long id;      // unique id

public:
    Edge();
    Edge(unsigned long id, Vertex<T> *o, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
    double getWeight() const;
    unsigned long getId() const;
    Vertex<T> *getDest() const;
};

template <class T>
Edge<T>::Edge(){}

template <class T>
Edge<T>::Edge(unsigned long id, Vertex<T> *o, Vertex<T> *d, double w): id(id), orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
unsigned long Edge<T>::getId() const {
    return id;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

#endif //CAL_T3G4_EDGE_H
