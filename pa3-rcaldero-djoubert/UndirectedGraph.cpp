#include "UndirectedGraph.hpp"
#include "Vertex.hpp"
#include <string>
#include <unordered_map>
#include <limits>
#include <vector>
#include <queue>
#include <iostream>
#include <tuple>

//typedef used for iterating through vertices
typedef std::unordered_map<std::string, Vertex*> verticesMap;

//typedef used for iterating through edges
typedef std::unordered_map<std::string, Edge> edgeMap; 

using namespace std;

// Undirected Graph destructor:
UndirectedGraph::~UndirectedGraph() {
  for (verticesMap::const_iterator vertexIt = vertices.begin(); vertexIt != 
       vertices.end(); vertexIt++){
    delete (vertexIt->second);
  }
  vertices.clear();
}

/*
* Inserts an edge into the graph. If an edge already exists between
* the vertices, updates the cost and length of the edge to match the
* passed parameters.
*
* If either of the named vertices does not exist, it is created.
*/
void UndirectedGraph::addEdge(const std::string &from, const std::string &to,
      unsigned int cost, unsigned int length){

  //if both exists
  if(vertices.find(from) != vertices.end() && vertices.find(to) != 
     vertices.end()) 
  {
    vertices[from]->addEdge(vertices[to],cost,length);
    vertices[to]->addEdge(vertices[from],cost,length);
  }

  //check if neither exists
  else if(vertices.find(from) == vertices.end() && vertices.find(to) == 
          vertices.end())
  {
    //create two new vertices
    Vertex *vertexFrom = new Vertex(from);
    Vertex *vertexTo = new Vertex(to);

    //add edges for both to each other
    vertexFrom->addEdge(vertexTo, cost, length);
    vertexTo->addEdge(vertexFrom, cost, length);

    vertices[from] = vertexTo;
    vertices[to] = vertexFrom;
  }  

  //otherwise, see if only from exists
  else if(vertices.find(from) != vertices.end() && vertices.find(to) == 
          vertices.end())
  {
    Vertex* toVertex = new Vertex(to);
    toVertex->addEdge(vertices[from], cost, length);
    vertices[from]->addEdge(toVertex,cost,length);

    vertices[to] = toVertex;    
  }

  //otherwise, see if only to exists
  else if(vertices.find(from) == vertices.end() && vertices.find(to) != vertices.end()){
    Vertex* fromVertex = new Vertex(from);
    fromVertex->addEdge(vertices[to], cost, length);
    vertices[to]->addEdge(fromVertex, cost, length);

    vertices[from] = fromVertex;   
  }
}

/**
* Returns the total cost of all edges in the graph.
*
* Since this graph is undirected, is calcualted as the cost
* of all Edges terminating at all Vertices, divided by 2.
*/
unsigned int UndirectedGraph::totalEdgeCost() const{
  unsigned int totalcost = 0;
  for (verticesMap::const_iterator myIt = vertices.begin(); myIt != 
    vertices.end(); myIt++) 
  {
    totalcost = totalcost + (myIt->second)->totalEdgeCost();
  }

  //return sum of edgecosts divided by 2 (since each edge counted twice)
  return (totalcost / 2);
}

/* Removes all edges from the graph except those necessary to
* form a minimum cost spanning tree of all vertices using Prim's
* algorithm.
*
* The graph must be in a state where such a spanning tree
* is possible. To call this method when a spanning tree is
* impossible is undefined behavior.
*/
void UndirectedGraph::minSpanningTree(){
  //create priority queue, with lower cost having higher priority
  std::priority_queue<Edge, std::vector<Edge>, CompareEdgeCosts> edgeQueue;

  //create vector of tuples, to hold what will be used for addEdge
  vector<tuple<string,string,int,int> > vectorTuple = vector<tuple<string,string,int,int> >();

  //set all vertices to not-visited
  for (verticesMap::const_iterator vertexIt = vertices.begin(); vertexIt != 
       vertices.end(); vertexIt++) 
  {
    (vertexIt->second)->setVisited(false);
  }

  //pick random (first) vertex, set field to true
  verticesMap::const_iterator startIt = vertices.begin();
  startIt->second->setVisited(true);

  //iterate through it's adjacent vertices
  std::unordered_map<std::string, Edge> firstEdges = startIt->second->getEdges();
  for(edgeMap::const_iterator edgeIt = firstEdges.begin(); edgeIt != 
      firstEdges.end(); edgeIt++) 
  {
    edgeQueue.push(edgeIt->second);
  }

  while( !edgeQueue.empty() ) {
    //check second condition: that there are unvisited edges
    bool stop = true;
    for (verticesMap::const_iterator vertexIt = vertices.begin(); 
         vertexIt != vertices.end(); vertexIt++) 
    {
      if (vertexIt->second->wasVisited() == false) {
        stop = false;
        break;
      }
    }
    if (stop) {
      break;
    }

    //get top edge from queue, if from vector has been visited, skip
    Edge checkE = edgeQueue.top();
    edgeQueue.pop();
    if (checkE.getTo()->wasVisited()) {
      continue;
    }

    //else set "to" vertices to visited, add edge to MST
    else {
      checkE.getTo()->setVisited(true);
      vectorTuple.push_back(make_tuple(checkE.getFrom()->getName(), checkE.getTo()->getName(), checkE.getCost(), checkE.getLength() ));

      //add edges to unvisited vertices to queue
      std::unordered_map<std::string, Edge> wEdges = checkE.getTo()->getEdges();
      for(edgeMap::const_iterator edgeIt = wEdges.begin(); edgeIt != 
          wEdges.end(); edgeIt++) {
        if (edgeIt->second.getTo()->wasVisited() == false) {
          edgeQueue.push(edgeIt->second);
        }
      }
    }
  } 

  //set graph vertices equal to the MST vertices
  for (verticesMap::const_iterator vertexIt = vertices.begin(); vertexIt != 
       vertices.end(); vertexIt++){
    delete (vertexIt->second);
  }
  vertices.clear();

  while (vectorTuple.empty() == false) {
    tuple<string,string,int,int> curr = vectorTuple.back();
    addEdge(get<0>(curr),get<1>(curr),get<2>(curr),get<3>(curr));
    vectorTuple.pop_back();
  }

}

/**
* Determines the combined distance from the given Vertex to all
* other Vertices in the graph using Dijkstra's algorithm.
*
* Returns max possible distance if the given Vertex does not appear
* in the graph, or if any of the Vertices in the graph are not
* reachable from the given Vertex. Otherwise, returns the combined
* distance.
*/
unsigned int UndirectedGraph::totalDistance(const std::string &from) {
  //set all other vertices to distance infinity, set input vertex's dist to 0
  for (verticesMap::const_iterator vertexIt = vertices.begin(); vertexIt != 
       vertices.end(); vertexIt++) 
  {
    (vertexIt->second)->setVisited(false);
    (vertexIt->second)->setDistance(std::numeric_limits<unsigned int>::max());  
  }

  //set start (from) vertex distance to 0 
  vertices[from]->setDistance(0);

  //create priority queue of pairs holding vertex and shortest path to that point
  std::priority_queue<std::pair<Vertex*, unsigned int>, std::vector<std::pair<Vertex*, unsigned int> >, 
    compVectorPairDistance> toBeChecked;

  //add from vertex to the priority queue to start
  std::pair <Vertex*, unsigned int> firstVertex(vertices[from], 0);
  toBeChecked.push(firstVertex);

  //run until no more vector's to check
  while(toBeChecked.size() != 0){
    //take top element from queue
    std::pair <Vertex*, unsigned int> currentVer = toBeChecked.top();
    toBeChecked.pop();

    //if top already visited, skip to next vertex
    if( std::get<0>(currentVer)->wasVisited() ){
      continue;
    }
    else {
      std::get<0>(currentVer)->setVisited(true);
    }

    //get edges of vertex being looked at
    std::unordered_map<std::string, Edge> edges = std::get<0>(currentVer)->getEdges();
    
    for(edgeMap::const_iterator visitIt = edges.begin(); visitIt != 
        edges.end(); visitIt++) {
      Vertex * w = visitIt->second.getTo();
      Edge wEdge = visitIt->second;
      
      if( !(w->wasVisited()) ){
        unsigned int bestPath = std::get<1>(currentVer) + wEdge.getLength();
        if( bestPath < (w->getDistance() ) ){
          w->setDistance(bestPath);
          std::pair <Vertex*, unsigned int> nextVertex(w, bestPath);
          toBeChecked.push(nextVertex);
        }
      }
    }
  } 

  //run through all vertices and add up the distance assigned via dijkstra
  int totaldistancefromX = 0;
  for (verticesMap::const_iterator vertexIt = vertices.begin(); vertexIt != 
       vertices.end(); vertexIt++) 
  {
    totaldistancefromX += (vertexIt->second)->getDistance();
  }
  return totaldistancefromX;
}

/**
* Determines the combined distance from all Vertices to all other
* Vertices in the graph.
*
* Returns max possible distance if the graph is not connected.
*/
unsigned int UndirectedGraph::totalDistance(){
  unsigned int totaldistance = 0;
  for (verticesMap::const_iterator myIt = vertices.begin(); myIt != 
       vertices.end(); myIt++) 
  {
    unsigned int distance = totalDistance(myIt->first);

    //run through each vertex and find totaldistance
    if (distance == std::numeric_limits<unsigned int>::max() ) {
      return std::numeric_limits<unsigned int>::max();
    }
    totaldistance += distance;
  }

  //return sum of vertices' sums of distances
  return totaldistance;
}

