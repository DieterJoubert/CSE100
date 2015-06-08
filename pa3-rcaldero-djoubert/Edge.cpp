#include "Edge.hpp"

// public methods for Edge

/**
 * Destructor for this class (edge)
 */
Edge::~Edge() {
  to = nullptr;
  from = nullptr;
  cost = 0;
  length = 0;
}

/**
 * Returns a pointer to the Vertex that this Edge originates
 * from.
 */
Vertex* Edge::getFrom() const {
  return from;
}

/**
 * Returns a pointer to the Vertex that this Edge terminates
 * at.
 */
Vertex* Edge::getTo() const {
  return to;
}

/**
 * Sets the cost of this Edge.
 */
void Edge::setCost(unsigned int cost) {
  this->cost = cost;
}

/**
 * Returns the cost of this Edge.
 */
unsigned int Edge::getCost() const {
  return cost;
}

/**
 * Sets the length of this Edge.
 */
void Edge::setLength(unsigned int length) {
  this->length = length;
}

/**
 * Returns the length of this Edge.
 */
unsigned int Edge::getLength() const {
  return length;
}
