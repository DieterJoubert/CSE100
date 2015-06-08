#include <queue>
#include <vector>
#include <fstream>
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <bitset>

using namespace std;

    /** Helper method for destruction of tree */
    void HCTree::freeNode( HCNode* node ){
      if( node == nullptr ){
        return;
      }
      if( node->c0 != NULL ){
        freeNode(node->c0);
      }
      if( node->c1 != NULL ){
        freeNode(node->c1);
      }
      node->c0 = 0;
      node->c1 = 0;
      node->p = 0;
      delete node;
    }

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs){

      // initialize priority queue
      std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> forest;

      // Pop all nodes out of vector and into priority queue
      for(int i = 0; i < (int) freqs.size(); i++){
        leaves[i] = new HCNode(freqs[i], i, 0, 0, 0);
        
        forest.push(leaves[i]);  // Place into priority queue
      }

      // Loop while > 1 tree in forest
      HCNode* firstNode = 0;
      HCNode* secondNode = 0;
      while(forest.size() > 1){
        // Remove two elements with smallest counts
        firstNode = forest.top();        
        forest.pop();
        secondNode = forest.top();
        forest.pop();

        // Combine into new tree
        int newRootCount = firstNode->count + secondNode->count;
        HCNode* newRoot = new HCNode(newRootCount, firstNode->symbol, 
          firstNode, secondNode, 0);
        firstNode->p = newRoot;
        secondNode->p = newRoot;
  
        // add new tree to forest
        forest.push(newRoot);
      }

      // return the tree
      root = forest.top();
    }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void HCTree::encode(byte symbol, BitOutputStream& out) const{
      vector<int> code = vector<int>();
      HCNode* cursor = leaves[symbol];

      while (cursor->p != 0) { 
        if ((cursor->p)->c0 == cursor) {
          code.push_back(0);
        }
        else {
          code.push_back(1);          
        }
        cursor = cursor->p;
      }

      while (!code.empty()) {
        out.writeBit(code.back());
        code.pop_back();
      }
    }

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void HCTree::encode(byte symbol, ofstream& out) const{
      vector<char> code = vector<char>();
      HCNode* cursor = leaves[symbol];

      while (cursor->p != 0) { 
        if ((cursor->p)->c0 == cursor) {
          code.push_back('0');
        }
        else {
          code.push_back('1');          
        }
        cursor = cursor->p;
      }

      while (!code.empty()) {
        out << code.back();
        code.pop_back();
      }
    }

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int HCTree::decode(BitInputStream& in) const{
      HCNode* cursor = root;
      while (cursor->c0 != 0 && cursor->c1 != 0) {
        char nextBinary = in.readBit();
        if (nextBinary == 0) {
          cursor = cursor->c0;
        }
        else if (nextBinary == 1) {
          cursor = cursor->c1;
        }
      }
      return cursor->symbol;
    }

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int HCTree::decode(ifstream& in) const {
      HCNode* cursor = root;
      while (cursor->c0 != 0 && cursor->c1 != 0) {
        char nextBinary = in.get();
        if (nextBinary == '0') {
          cursor = cursor->c0;
        }
        else if (nextBinary == '1') {
          cursor = cursor->c1;
        }
      }
      return cursor->symbol;
    }

    /** Uses the bitoutputstream to build the tree from the pre-order iteration
     *  printed as the header of the file. Uses the recurse preOrder method on 
     *  root, passing a reference to the BitOutputStream to do so
     */    
    void HCTree::buildBitHeader(BitOutputStream& out) const {
      preOrder(root, out);
    }

    /** Helper function to output the nodes of the tree recursively in a 
     *  pre-order traversal
     */
    void HCTree::preOrder(HCNode* node, BitOutputStream& outStream) const {
      //base case
      if (node == NULL) {           
        return;
      }

      //check if leaf
      if(node->c0 == NULL && node->c1 == NULL) {

        //if leaf, output bit 1 followed by 8 bits representing symbol
        std::bitset<8> x(node->symbol); 
        outStream.writeBit((int) 1);        
        for (int j = 7; j>=0; j--) {
          outStream.writeBit( (int) x[j]);
        }        
      }
      else {
        //otherwise not leaf, output bit 0
        outStream.writeBit((int) 0);
      }

      preOrder(node->c0,outStream);
      preOrder(node->c1,outStream);
    }  

    /** Reading in the header from compressed bits, and build tree.
     *  Does so by repeating pre-order traversal used to build header.
     */
    void HCTree::readBitHeader(BitInputStream& in) {
      root = new HCNode(0, 0, nullptr, nullptr, nullptr);
      HCNode* cursor = root;
      int leafCount = 0;

      //already have root, so read in first bit before loop (will be 0) 
      int nextBit = in.readBit();

      //loop until all 256 leaves have been created
      while (leafCount <256) {

        nextBit = in.readBit();

        if (nextBit == 0) {
          //left child empty, create left child and move cursor to it
          if ( cursor->c0 == 0) {
            ( cursor->c0) = new HCNode(0,0,0,0,cursor);
            cursor = cursor->c0;
          }
          //right child empty, create left child and move cursor to it
          else if ( cursor->c1 == 0) {
            ( cursor->c1) = new HCNode(0,0,0,0,cursor);
            cursor = cursor->c1;
          }
        }

        else if (nextBit == 1) {

          //1 is a leaf, so read in symbol from next 8 bits
          std::bitset<8> number;
          for (int j=7 ; j >= 0; j--) {
            number[j] = in.readBit();
          }

          //left child empty, create it with symbol, don't move cursor
          if (cursor->c0 == 0) {
            (cursor->c0) = new HCNode(0,number.to_ulong(),0,0,cursor);
          }

          //right child empty, create it with symbol, don't move cursor
          else if ( cursor->c1 == 0) {
            ( cursor->c1) = new HCNode(0,number.to_ulong(),0,0,cursor);

            //move cursor to next spot with empty right child
            while ( cursor->c1 != 0 && cursor->c0 != 0 && cursor->p != 0) {
              cursor = cursor->p;

            }
          }
          leafCount++;
        }
      }
    }


