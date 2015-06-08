#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */
  virtual ~BST() {
    if (root == nullptr)
      return;
    else 
      freeNode(root);
    isize = 0;
    root = nullptr;   
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */
  virtual std::pair<iterator,bool> insert(const Data& item) {
    //either add 0 to isize if duplicate, or 1
    BSTNode<Data>* p = root, *prev = 0;

    //if root null, creates root node
    if (root == 0) {
      root = new BSTNode<Data>(item);
      BSTIterator<Data> myIterator(root);
      std::pair <iterator,bool> returnPair = std::make_pair(myIterator, true);
      isize++;
      return returnPair;
    }

    //else runs through nodes to find insert point
    while (p != 0) {
      prev = p;
      if (item == p->data) {
        BSTIterator<Data> myIterator(p);
        std::pair <iterator,bool> returnPair = std::make_pair(myIterator, false);
        return returnPair;
      }
      else if (item < p->data) {
        p = p->left;
      }
      else if (item > p->data) {
        p = p->right;
      }
    }

    BSTNode<Data>* newNode = new BSTNode<Data>(item);

    //check if item should be inserted as left or right child
    if (item <  prev->data) {
      prev->left = newNode;
    }
    else {
      prev->right = newNode;
    }

    //insert item, return pair with iterator on item
    newNode->parent = prev;
    BSTIterator<Data> myIterator(newNode);
    isize++;
    std::pair <iterator,bool> returnPair = std::make_pair(myIterator, true);
    return returnPair;
  }

  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */
  iterator find(const Data& item) const {
    BSTNode<Data>* cursor = root;
    while (cursor != nullptr) {
      if (cursor->data == item)
        return typename BST<Data>::iterator(cursor);
      else if (cursor->data < item)
        cursor = cursor->right;
      else
        cursor = cursor->left;
    }
    return end();
  }

 
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */
  void clear() {
    if (root == nullptr)
      return;
    else freeNode(root);
    isize = 0;
    root = nullptr;
  }

  /** 
   * Utility function to remove all nodes  
   */
  void freeNode( BSTNode<Data>* t )
  {
    if( t == NULL )
        return;
    if( t->left != NULL )
        freeNode( t->left );
    if( t->right != NULL )
        freeNode( t->right );
    
    delete t;
    return;
  } 

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
    if (isize == 0)
      return true;
    else 
      return false;
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
    BSTNode<Data>* cursor = root;
    while (cursor->left != nullptr) {
      cursor = cursor->left;
    }
    return typename BST<Data>::iterator(cursor);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
