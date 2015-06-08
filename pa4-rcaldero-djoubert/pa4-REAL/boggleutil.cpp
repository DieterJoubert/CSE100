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

//------------------------------------------------------------

MWTNode::MWTNode() {
  //create child for every letter of alphabet
  children = new MWTNode*[26];
  for (int i = 0; i <27; i++) {
  	children[i]=(MWTNode*)0;
  }
  exists = false;
  parent = (MWTNode*)0;
}

bool MWTNode::getExists() {
  return exists;
}

void MWTNode::setExists(bool state) {
  exists = state;
}
