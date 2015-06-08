#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BogglePlayer p;

  std::set<string> lex;
  std::set<string> results;

  std::ifstream in("lex.txt");
  
  // Load the lexicon from file
  string word;
  while(std::getline(in, word))
    lex.insert(word);
  
  in.close();

  std::cout << "wc: " << lex.size() << "\n";


  // Load the board dice from file
  int rows;
  int cols;
  in.open("brd.txt");

  in >> rows;
  in >> cols;
   
  std::cout << "r: " << rows << " c: " << cols << "\n";

  std::string **brd = new std::string*[rows];
  
  for (int i = 0; i < rows; ++i) {
    std::string *row = new std::string[cols];

    for (int j = 0; j < cols; ++j) {
      in >> row[j];
    }

    brd[i] = row;
  }

  in.close();

  // Display the board 
  for (int i = 0; i < rows; ++i) {

    for (int j = 0; j < cols; ++j) {
      std::string* r = brd[i];
      std::cout << r[j];
    }

    std::cout << "\n";

  }

  // Prepare the BogglePlayer object
  p.buildLexicon(lex);
  p.setBoard(rows, cols, brd);

  // Get the results
  p.getAllValidWords(2, &results);

  std::cout << "wc: " << results.size() << "\n";

  std::set<string>::iterator i = results.begin();
  std::set<string>::iterator e = results.end();

  while (i != e) {
   std::cout << *i++ << "\n";
  }

  for(int i = 0; i < rows; i++){
    delete[] brd[i];
  }
  delete[] brd;

  return 0;
}
