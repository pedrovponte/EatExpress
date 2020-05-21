/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include "MutablePriorityQueue.h"
#include "Vertex.h"
#include "Edge.h"
#include <iostream>

using namespace std;

#define INF std::numeric_limits<double>::max()

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    map<unsigned long, VertexType> vTypes; //save restaurants
	Vertex<T> * initSingleSource(const T &orig);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	double ** W = nullptr;   // dist
	int **P = nullptr;   // path
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in, VertexType type = OTHER);
	bool addEdge(unsigned long id, const T &sourc, const T &dest, double w);
    const Edge<T> & getEdge(const T &sourc, const T &dest) const;
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

    void setVertexSet(const vector<Vertex<T>*> vertexSet);

    int findVertexIdx(const T &in) const;

    map<unsigned long, VertexType> getVTypes() const;

    void setVTypes(const map<unsigned long, VertexType>);

    // Single source
	void dijkstraShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;
	vector<T> getPathTo(const T &dest) const;

	// All pairs shortest Path
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
    double ** getDistancesMatrix() const;
    void readDistancesMatrix(string filename);
    void readPredecessorMatrix(string filename);
    void saveDistancesMatrix(string filename);
    void savePredecessorMatrix(string filename);
    double getDist(int orig, int dest) const;
	~Graph();

    bool addBidirectionalEdge(unsigned long idSourc, unsigned  long idDest, const T &sourc, const T &dest, double w);

    vector<T> dfs() const;
    vector<T> dfs(T info) const;
    void dfsVisit(Vertex<T> *v, vector<T> &res) const;
};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet){
        if (v->info == in)
            return v;
	}
	return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, VertexType type) {
	if (findVertex(in) != nullptr)
		return false;
	vertexSet.push_back(new Vertex<T>(in,type));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(unsigned long id, const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr){
        return false;
	}
	v1->addEdge(id, v2, w);
	return true;
}

template <class T>
const Edge<T> & Graph<T>::getEdge(const T &sourc, const T &dest) const{
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);

    if (v1 == nullptr || v2 == nullptr){
        throw NullEdgeException();
    }

    for(unsigned int i = 0; i < v1->adj.size(); i++){
        if(v1->adj[i].dest == v2)
            return v1->adj[i];
    }
    throw NullEdgeException();
}

template<class T>
map<unsigned long, VertexType> Graph<T>::getVTypes() const{
    return vTypes;
}

template<class T>
void Graph<T>::setVTypes(const map<unsigned long, VertexType> vTypes) {
    this->vTypes = vTypes;
}



/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for(auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		for(auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
    vector<T> res;
    Vertex<T> * d = findVertex(dest);
    // TODO
    typename vector<Vertex<T>*>::const_iterator it;
    res.push_back(d->getInfo());
    while(d->getPath() != NULL){
        d = d->getPath();
        res.push_back(d->getInfo());
    }
    reverse(res.begin(),res.end());
    return res;
}

/**************** All Pairs Shortest Path  ***************/

template <class T>
void deleteMatrix(T **m, int n) {
	if (m != nullptr) {
		for (int i = 0; i < n; i++)
			if (m[i] != nullptr)
				delete [] m[i];
		delete [] m;
	}
}

template <class T>
Graph<T>::~Graph() {
	deleteMatrix(W, vertexSet.size());
	deleteMatrix(P, vertexSet.size());
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	unsigned n = vertexSet.size();
	deleteMatrix(W, n);
	deleteMatrix(P, n);
	W = new double *[n];
	P = new int *[n];
	for (unsigned i = 0; i < n; i++) {
		W[i] = new double[n];
		P[i] = new int[n];
		for (unsigned j = 0; j < n; j++) {
			W[i][j] = i == j? 0 : INF;
			P[i][j] = -1;
		}
		for (auto e : vertexSet[i]->adj) {
			int j = findVertexIdx(e.dest->info);
			W[i][j]  = e.weight;
			P[i][j]  = i;
		}
	}

	for(unsigned k = 0; k < n; k++)
		for(unsigned i = 0; i < n; i++)
			for(unsigned j = 0; j < n; j++) {
				if(W[i][k] == INF || W[k][j] == INF)
					continue; // avoid overflow
				double val = W[i][k] + W[k][j];
				if (val < W[i][j]) {
					W[i][j] = val;
					P[i][j] = P[k][j];
				}
			}
}


template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	int i = findVertexIdx(orig);
	int j = findVertexIdx(dest);
	if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
		return res;
	for ( ; j != -1; j = P[i][j])
		res.push_back(vertexSet[j]->info);
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
double ** Graph<T>::getDistancesMatrix() const{
    return W;
}

template<class T>
void Graph<T>::readDistancesMatrix(string filename){
    ifstream in("../" + filename);
    string s;
    int n = getNumVertex();
    W = new double *[n];
    for (unsigned i = 0; i < n; i++)
        W[i] = new double[n];

    if(in.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                getline(in,s,' ');
                W[i][j] = stod(s);
            }
        }
    }
}

template<class T>
void Graph<T>::readPredecessorMatrix(string filename){
    ifstream in("../" + filename);
    string s;
    int n = getNumVertex();

    P = new int *[n];
    for (unsigned i = 0; i < n; i++)
        P[i] = new int[n];

    if(in.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                getline(in,s,' ');
                P[i][j] = stoi(s);
            }
        }
    }
}

template<class T>
void Graph<T>::saveDistancesMatrix(string filename){
    ofstream out("../" + filename);
    int n = getNumVertex();
    if(out.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                out << W[i][j] << " ";
            }
            out << endl;
        }
    }
}

template<class T>
void Graph<T>::savePredecessorMatrix(string filename){
    ofstream out("../" + filename);
    int n = getNumVertex();
    if(out.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                out << P[i][j] << " ";
            }
            out << endl;
        }
    }
}

template<class T>
double Graph<T>::getDist(int orig, int dest) const{
    return W[orig][dest];
}

template <class T>
bool Graph<T>::addBidirectionalEdge(unsigned long idSourc, unsigned  long idDest, const T &sourc, const T &dest, double w) {
    // TODO
    return addEdge(idSourc, sourc,dest,w) && addEdge(idDest, dest,sourc,w);
}

template<class T>
void Graph<T>::setVertexSet(const vector<Vertex<T>*> vertexSet) {
    this->vertexSet.clear();

    this->vertexSet.insert(this->vertexSet.begin(), vertexSet.begin(), vertexSet.end());
}


/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    for (int i = 0; i < this->vertexSet.size(); i++)
        vertexSet[i]->visited = false;

    vector<T> res = vector<T>();

    for (int i = 0; i < this->vertexSet.size(); i++)
        if (!vertexSet[i]->visited)
            dfsVisit(vertexSet[i],res);

    return res;
}

template <class T>
vector<T> Graph<T>::dfs(T info) const {
    for (int i = 0; i < this->vertexSet.size(); i++)
        vertexSet[i]->visited = false;

    vector<T> res = vector<T>();

    Vertex<T> * vertex = this->findVertex(info);

    if (!vertex->visited)
        dfsVisit(vertex,res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (int i = 0; i < v->adj.size(); ++i) {
        if (!v->adj[i].dest->visited)
            dfsVisit(v->adj[i].dest,res);
    }
}



#endif /* GRAPH_H_ */
