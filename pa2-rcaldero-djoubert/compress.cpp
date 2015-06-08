#include <iostream>
#include <fstream>
#include <iostream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <bitset>

typedef unsigned char byte;

using namespace std;

int main(int argc, char** argv){
  HCTree tree;
  ifstream inFile;
  ofstream outFile;
  
  if( argc != 3 ){ 
    cout << "Error: Please supply three arguments." << endl;
    cout << "Usage: ./compress [file to compress] [name of compressed file]" << endl;
    return 1; 
  }

  inFile.open( argv[1], ios::binary );

  if (!(inFile.is_open()) ){
    cout << "Error: " << argv[1] << " does not exist in this directory." << endl;
    return 1;
  }

  int nextByte;
  outFile.open( argv[2], ios::binary);

  if( inFile.peek() == EOF){
    inFile.close();
    outFile.close();
    return 1;
  }

  std::ostream & outStream(outFile);
  BitOutputStream out(outStream);

  // Vector of byte frequencies
  std::vector<int> freqs = vector<int>(256, (byte) 0);

  while (1) {
    nextByte = inFile.get();
    if (inFile.eof()) break;
    freqs[nextByte]++;
  }  
  
  // build the tree
  tree.build(freqs);
  tree.buildBitHeader(out);

  int totalFreq = 0;
  for (int i=0; i<256; i++) {
    totalFreq = totalFreq + freqs[i];
  }
  std::bitset<32> x(totalFreq);
  for (int j = 31; j>=0; j--) {
    out.writeBit(x[j]);
  }

  inFile.clear();
  inFile.seekg(0, ios::beg);

  while (1) {
    nextByte = inFile.get();
    if (inFile.eof()) {
      out.flush();
      break;
    }
    tree.encode(nextByte, out);
  }

  inFile.close();
  outFile.close();
  
}
