#include "boggleplayer.h"
#include "boggleplayer.cpp"
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include "boggleutil.cpp"

#include <iostream>
#include <fstream>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {  
  BaseBogglePlayer * p = new BogglePlayer(); 

  std::string line;
  std::ifstream myfile("lex.txt");
  std::set<std::string> myLines;
  while (std::getline(myfile, line))
  {
    myLines.insert(line);
  }

  p->buildLexicon(myLines);

  int height = 20;
  int width = 23;

  std::string ** board;
  board = new std::string*[height];
  for (unsigned int r=0; r<height; r++) {
    board[r] = new std::string[width];
  }

  myfile.close();

  std::string line2;
  std::ifstream mybrd("brd.txt");

  std::getline(mybrd, line2);
  std::getline(mybrd, line2);

    for(unsigned int r=0; r<height ;r++) {
      for(unsigned int c=0; c<width ;c++) {
        std::getline(mybrd, line2);
        //cout << "BOARD: " + line2 << endl;
        board[r][c] = line2;
      }
    }

  mybrd.close();

  p->setBoard(20,23,board);

  cout << "BOARD SET SUCCESSFULLY" << endl;


  set<string> words;

  p->getAllValidWords(2,&words);
  if (words.size() == 0) {
    cout << "ERROR: all valid words is empty" << endl;
  }
  cout << "--------VALID WORDS--------" << endl;
  for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
    cout << *it << endl;
  }  

};


