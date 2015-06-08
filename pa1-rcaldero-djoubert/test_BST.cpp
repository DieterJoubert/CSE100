#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(1);
  v.push_back(100);
  v.push_back(-33);

  /* Create an instance of BST holding int */
  BST<int> b;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> pr = b.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
      return -1;
    }  
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  for(; vit != ven; ++vit) {
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator en = b.end();
  BST<int>::iterator it = b.begin();
  // BSTNode<int> cursor = *(b.find(*vit)).curr;
  for(; vit != ven; ++vit) {
    if(! (it != en) ) {
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    cout << "Parent:" << it.currParent() << endl;
    cout << "Left:" << it.currLeft() << endl;
    cout << "Right:" << it.currRight() << endl;
    cout << " " << endl;    
    
    // cout << cursor << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }

  cout << "BST1 OK." << endl;
  cout << "-------------------------------" << endl;

  // Test second BST
  vector<int> w;
  w.push_back(-42);
  w.push_back(2);
  w.push_back(42);
  w.push_back(3);
  w.push_back(24);
  w.push_back(5);
  w.push_back(-2);
  w.push_back(-3);
  w.push_back(24);
  w.push_back(10);
  w.push_back(100);
  
  BST<int> c;
  
  
  // Implement test to ensure pair is returning correctly
  vector<int>::iterator wit = w.begin();
  vector<int>::iterator wen = w.end();
  vector<int> valuesSeen;
  while( wit != w.end() ) {
    std::pair<BST<int>::iterator,bool> ps = c.insert(*wit);
    // If ps.second is false, a duplicate element is in the vector
    if( ! ps.second ) { 
      cout << *wit << " is already in tree and was not inserted." << endl;
      // erase duplicate elment from vector, wit now points to next elem
      w.erase(w.begin() + valuesSeen.size());
    }
    else ++wit; // only increment if elem was unique
    valuesSeen.push_back(*wit);
  }
  
  /* Test size. */
  cout << "Size is: " << c.size() << endl;
  if(c.size() != w.size()) {
    cout << "... which is incorrect. Should be " << w.size() << endl;
    return -1;
  }

  /* Test find return value. */
  vit = w.begin();
  for(; wit != wen; ++wit) {
    if(*(c.find(*wit)) != *wit) {
      cout << "Incorrect return value when finding " << *wit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(w.begin(),w.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  wit = w.begin();
  wen = w.end();
  en = c.end();
  it = c.begin();
  for(; wit != wen; ++wit) {
    if(! (it != en) ) {
      cout << *it << "," << *wit << ": Early termination of BST iteration." 
           << endl;

      return -1;
    }
    cout << *it << endl;
    cout << "Parent:" << it.currParent() << endl;
    cout << "Left:" << it.currLeft() << endl;
    cout << "Right:" << it.currRight() << endl;
    cout << " " << endl;
    
    if(*it != *wit) {
      cout << *it << "," << *wit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }

  cout << "BST2 OK." << endl;
  cout << "-------------------------------" << endl;

  //Create two trees
  BST<float> floatBST1;
  BST<float> floatBST2;

  //Add elements to tree
  floatBST1.insert(1.0);
  floatBST1.insert(-2.0);
  floatBST1.insert(3.3);
  floatBST1.insert(5.0);
  floatBST1.insert(7.0);
  floatBST1.insert(8.5);

  //Add duplicate elements to second tree
  floatBST2.insert(1.0);
  floatBST2.insert(-2.0);
  floatBST2.insert(-2.0);
  floatBST2.insert(-2.0);  
  floatBST2.insert(3.3);
  floatBST2.insert(5.0);
  floatBST2.insert(5.0);  
  floatBST2.insert(7.0);
  floatBST2.insert(8.5);
  floatBST2.insert(8.5);
  floatBST2.insert(8.5);  

  cout << "Size of first BST: " << floatBST1.size() << endl;
  cout << "Size of second BST: " << floatBST2.size() << endl;
  if (floatBST1.size() != floatBST2.size()) {
    cout << "INCORRECT" << endl;
    return -1;
  }  
  
  BST<float>::iterator fit1 = floatBST1.begin();
  BST<float>::iterator fit2 = floatBST2.begin();

  //iterate through trees, make sure no duplicates are read
  for (unsigned int i = 0; i < floatBST1.size(); i++) {
    if (*fit1 != *fit2) {
      cout << "TREES ARE NOT THE SAME. ERROR." << endl;
      return -1;
    }
    cout << *fit1 << endl;
    cout << "Parent:" << fit1.currParent() << endl;
    cout << "Left:" << fit1.currLeft() << endl;
    cout << "Right:" << fit1.currRight() << endl;
    cout << " " << endl;        

    ++fit1;
    ++fit2;
  }

  cout << "BST3 ITERATION OK." << endl;
  cout << "-------------------------------" << endl;

  //check if clear works correctly
  floatBST1.clear();
  floatBST2.clear();
  if (!floatBST1.empty()) {
    cout << "Tree not empty. Fix clear()" << endl;
    return -1;
  }
  if (!floatBST2.empty()) {
    cout << "Tree not empty. Fix clear()" << endl;
    return -1;
  }

  if (floatBST1.size() != floatBST2.size()) {
    cout << "TREES ARE NOT THE SAME. ERROR." << endl;
    return -1;
  }

  cout << "BST3 CLEARING OK." << endl;
  cout << "-------------------------------" << endl;

  //Add elements to tree
  floatBST1.insert(5.0);  
  floatBST1.insert(1.0);
  floatBST1.insert(-2.0);
  floatBST1.insert(3.3);
  floatBST1.insert(7.0);
  floatBST1.insert(8.5);

  //Add duplicate elements to second tree
  floatBST2.insert(8.5);    
  floatBST2.insert(-2.0);
  floatBST2.insert(-2.0);  
  floatBST2.insert(7.0);
  floatBST2.insert(8.5);  
  floatBST2.insert(1.0);
  floatBST2.insert(-2.0);
  floatBST2.insert(3.3);
  floatBST2.insert(8.5);
  floatBST2.insert(5.0);
  floatBST2.insert(5.0);    

  cout << "Size of first BST: " << floatBST1.size() << endl;
  cout << "Size of second BST: " << floatBST2.size() << endl;
  if (floatBST1.size() != floatBST2.size()) {
    cout << "INCORRECT" << endl;
    return -1;
  }  
  
  fit1 = floatBST1.begin();
  fit2 = floatBST2.begin();

  //iterate through trees, make sure no duplicates are read
  for (unsigned int i = 0; i < floatBST1.size(); i++) {
    if (*fit1 != *fit2) {
      cout << "TREES ARE NOT THE SAME. ERROR." << endl;
      return -1;
    }
    cout << *fit1 << endl;
    cout << "Parent:" << fit1.currParent() << endl;
    cout << "Left:" << fit1.currLeft() << endl;
    cout << "Right:" << fit1.currRight() << endl;
    cout << " " << endl;        

    ++fit1;
    ++fit2;
  }

  cout << "BST3 SECOND ITERATION OK." << endl;
  cout << "-------------------------------" << endl;



}
