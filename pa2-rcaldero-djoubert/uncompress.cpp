#include <iostream>
#include <fstream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <bitset>
#include <string>

typedef unsigned char byte;

using namespace std;

int main(int argc, char** argv){
  HCTree tree;
  ifstream inFile;
  ofstream outFile;

  if( argc != 3 ){ 
    cout << "Error: Please supply three arguments." << endl;
    cout << "Usage: ./compress [file to uncompress] [name of uncompressed file]" << endl;
    return 1; 
  }

  inFile.open( argv[1], ios::binary );

  if (!(inFile.is_open()) ){
    cout << "Error: " << argv[1] << " does not exist in this directory." << endl;
    return 1;
  }

  outFile.open( argv[2], ios::binary );

  std::istream & inStream(inFile);
  BitInputStream in(inStream);  

  //read header
  tree.readBitHeader(in);

  //read how many bytes will be sent to output
  std::bitset<32> number;
  for (int j= 31; j >= 0; j--) {
    number[j] = in.readBit();
  }
  int bytesToOut = number.to_ulong();

  //counter for how many bytes have been outputted
  int bytesOuted = 0;

  //decode the actual code
  while (1) {
    byte next = tree.decode(in);
    bytesOuted++;
    if( inFile.eof()) break;
    outFile.put(next);
    if (bytesOuted == bytesToOut) {
      break;
    }
  }

  //finished, close input and output files
  inFile.close();
  outFile.close();
};

