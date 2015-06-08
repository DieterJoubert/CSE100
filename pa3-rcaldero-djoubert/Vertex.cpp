#include "Vertex.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <iterator>

typedef std::unordered_map<std::string, Edge> edgeMap; 

/* Destroy the vertex */
Vertex::~Vertex(){
  clearEdges();
  distance = 0;
  visited = 0;
}
/**
 * Add an edge to the input Vertex. If an edge already exists to the given
 * vertex, updates the cost and length of the edge to match the
 * passed parameters.
 */
bool Vertex::addEdge(Vertex *to, unsigned int cost, unsigned int length){

   //check if edge already exists in map of edges
  if (edges.find(to->getName()) == edges.end() ) {
    //add Edge to this vertex's unordered_map
   	Edge newEdgeThis = Edge(this, to, cost, length);
   	std::pair<std::string, Edge> myTest (to->getName(),newEdgeThis);   
   	edges.insert(myTest);

  	//return true, new edge added
  	return true;
  }

  //else edge must exists in map
  else {
    //find "to" vertex, set cost and length
    edges.at(to->getName()).setCost(cost);
    edges.at(to->getName()).setLength(length);

    //find "from" vertex, set cost and length
    (to->edges).at(this->getName()).setCost(cost);
    (to->edges).at(this->getName()).setLength(length);

	  //no new edge added, old edge updated, so return false
	  return false;
  }	

}

/**
 * Returns the Vertex's name.
 */
const std::string& Vertex::getName() const{
   return name;
}

/**
 * Gets the Vertex's distance value.
 */
unsigned int Vertex::getDistance() const{
   return distance;
}

/**
 * Sets the Vertex's distance value.
 */
void Vertex::setDistance(unsigned int distance) {
  	this->distance = distance;
}

/**
 * Gets the Vertex's visited state.
 */
bool Vertex::wasVisited() const {
	return visited;
}

/**
 * Sets the Vertex's visited state.
 */
void Vertex::setVisited(bool visited) {
	this->visited = visited;
}

/**
 * Clears all edges from this Vertex.
 */
void Vertex::clearEdges() {
  edges.clear();
}

/**
 * Gets total cost of all edges terminating at this Vertex.
 */
unsigned int Vertex::totalEdgeCost() const {
	int totalCost = 0;
	for(edgeMap::const_iterator myIterator = edges.begin(); myIterator != 
      edges.end(); myIterator++) {
		totalCost += (myIterator->second).getCost();
	}
	return totalCost;
}
