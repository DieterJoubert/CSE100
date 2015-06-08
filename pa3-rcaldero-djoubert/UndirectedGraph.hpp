#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

#include <string>
#include <unordered_map>
#include "Vertex.hpp"
#include "Edge.hpp"

/**
 * Comparison class for priority queue in building MST
 */
class CompareEdgeCosts {
  public:
    bool operator()(Edge& e1, Edge& e2) const{
      return e1.getCost() >= e2.getCost();
  }
};

/**
 * Comparison class for priority queue in dijkstra's algorithm
 */
class compVectorPairDistance {
  public:
    bool operator()(std::pair<Vertex*, unsigned int> p1, std::pair<Vertex*, unsigned int> p2) {
      return p1.second > p2.second;
  }
};

/**
 * Implements an undirected graph. Any edge in the graph
 * represents a bidirectional connection between two vertices.
 * 
 * Implements methods for producing a minimum spanning tree of the
 * graph, as well as calculating the total length of the shortest
 * paths between each pair of vertices.
 */
class UndirectedGraph {
  public:
    /**
     * Constructs an empty UndirectedGraph with no vertices and
     * no edges.
     */
    UndirectedGraph() {
        vertices = std::unordered_map<std::string, Vertex*>();
    }

    /**
     * Destructs an UndirectedGraph.
     */
    ~UndirectedGraph();
    
    /**
     * Inserts an edge into the graph. If an edge already exists between
     * the vertices, updates the cost and length of the edge to match the
     * passed parameters.
     *
     * If either of the named vertices does not exist, it is created.
     */
    void addEdge(const std::string &from, const std::string &to,
            unsigned int cost, unsigned int length);

    /**
     * Returns the total cost of all edges in the graph.
     *
     * Since this graph is undirected, is calcualted as the cost
     * of all Edges terminating at all Vertices, divided by 2.
     */
    unsigned int totalEdgeCost() const;
    
    /**
     * Removes all edges from the graph except those necessary to
     * form a minimum cost spanning tree of all vertices using Prim's
     * algorithm.
     *
     * The graph must be in a state where such a spanning tree
     * is possible. To call this method when a spanning tree is
     * impossible is undefined behavior.
     */
    void minSpanningTree();
    
    /**
     * Determines the combined distance from the given Vertex to all
     * other Vertices in the graph using Dijkstra's algorithm.
     *
     * Returns max possible distance if the given Vertex does not appear
     * in the graph, or if any of the Vertices in the graph are not
     * reachable from the given Vertex. Otherwise, returns the combined
     * distance.
     */
    unsigned int totalDistance(const std::string &from);
    
    /**
     * Determines the combined distance from all Vertices to all other
     * Vertices in the graph.
     *
     * Returns max possible distance if the graph is not connected.
     */
    unsigned int totalDistance();
    
  private:
    /**
     * Map of vertex name to Vertex.
     */
    std::unordered_map<std::string, Vertex*> vertices;
};

#endif
