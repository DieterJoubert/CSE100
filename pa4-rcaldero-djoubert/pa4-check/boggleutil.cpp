#include "boggleutil.h"

bool BoardNode::getVisited() {
  return visited;
}

void BoardNode::setVisited(bool newState) {
  visited = newState;
}

const std::string& BoardNode::getFace() const {
  return face;
}
