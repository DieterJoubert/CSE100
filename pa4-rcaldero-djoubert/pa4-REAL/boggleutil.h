#ifndef BOARDNODE_H
#define BOARDNODE_H

#include <string>

class BoardNode {
  public:
    //empty constructor for setting up initial array
    BoardNode() { };

    //constructor that takes in string to indicate dice face
    BoardNode(const std::string &dieFace): face(dieFace), visited(false) { };

    ~BoardNode() { };
    
    //returns state of whether node was visited, useful for traversal (prevent cycles)
    bool getVisited();

    //set state of whether node has been visited,
    void setVisited(bool newState);

    //returns the string on the face of this node (i.e. dice)
    const std::string& getFace() const;

  private:
    //the string (usually of length 1) on this "dice"
    std::string face;

    //bool used to indicate whether node has been hit via traversal
    bool visited;

};

#endif //BOARDNODE_H

//------------------------------------------------------------------------------------

#ifndef MWTNode_H
#define MWTNode_H

#include <string>

class MWTNode {

  friend class BogglePlayer;
  public:
    //empty constructor for setting up initial array
    MWTNode();

    ~MWTNode() { };
    
    //returns state of whether node was visited, useful for traversal (prevent cycles)
    bool getExists();

    void setExists(bool state);

  //private:
    //the children of this node of the MWT
    MWTNode** children;
    MWTNode* parent;

    //bool used to indicate whether node has been hit via traversal
    bool exists;

};

#endif //MWTNode_H
