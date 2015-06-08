#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

/**
 * Represents an edge in a graph.
 *
 * Maintains pointers to the vertices that the edge originates 
 * from and terminates at. Edges have both a cost and a length,
 * which are both non-negative integers.
 *
 * Follows value semantics, so can be copy constructed.
 */
class Edge {
  public:
    /**
     * Constructs an Edge from the given parameters.
     */
    Edge(Vertex *from, Vertex *to,
            unsigned int cost = 0,
            unsigned int length = 0): from(from), to(to), cost(cost), 
	    length(length) { };

    /**
     * Destructor for this class (edge)
     */
    ~Edge();

    /**
     * Returns a pointer to the Vertex that this Edge originates
     * from.
     */
    Vertex * getFrom() const;
    
    /**
     * Returns a pointer to the Vertex that this Edge terminates
     * at.
     */
    Vertex * getTo() const;

    /**
     * Sets the cost of this Edge.
     */
    void setCost(unsigned int cost);

    /**
     * Returns the cost of this Edge.
     */
    unsigned int getCost() const;

    /**
     * Sets the length of this Edge.
     */
    void setLength(unsigned int length);

    /**
     * Returns the length of this Edge.
     */
    unsigned int getLength() const;
    
  //private members, all variables, describing the edge
  private:
    /**
     * Vertex that this Edge originates from.
     */
    Vertex *from;

    /**
     * Vertex that this Edge terminates at.
     */
    Vertex *to;

    /**
     * Cost of this Edge.
     */
    unsigned int cost;

    /**
     * Length of this Edge.
     */
    unsigned int length;
};

#endif
