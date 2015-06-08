#include "boggleutil.h"

//see whether dice has been used in forming word
bool BoardNode::getVisited() {
  return visited;
}

//sets whether dice has been visited, used by finding word path
void BoardNode::setVisited(bool newState) {
  visited = newState;
}

//returns the string representing the face of this dice
const std::string& BoardNode::getFace() const {
  return face;
}

//------------------------------------------------------------

//constructor for MWTNode used by boggleplayer to represent multiwaytrie nodes
MWTNode::MWTNode() {
  //create child for every letter of alphabet
  children = new MWTNode*[26];
  for (int i = 0; i<26; i++) {
    children[i] = 0;
  }
  exists = false;
  parent = 0;
}

//destructor for MWTNode
MWTNode::~MWTNode(){
  for(int i = 0; i<26; i++){
    delete children[i];
  }
  delete[] children;
}

//returns bool exists, used to see if this is end-path of valid word
bool MWTNode::getExists() {
  return exists;
}

//sets exist, used when creating the trie
void MWTNode::setExists(bool state) {
  exists = state;
}
