#include "boggleplayer.h"
#include "boggleutil.h"

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

BogglePlayer::~BogglePlayer() {
  for(unsigned int i = 0; i < height; i++) {  
    delete[] board[i];
  }
  delete[] board;
}


void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
  //delete board, in case setBoard has been called before
  delete[] board;

  //set size of array of arrays to number of rows
  board = new BoardNode*[rows];

  //each array in array of arrays has size equal to columns
  for (unsigned int r=0; r < rows; r++) {
    board[r] = new BoardNode[cols];
  }

  //set width and height, useful for isOnBoard
  width = cols;
  height = rows;

  //now fill the "board" with the input diceArray's elements
  for(unsigned int r=0; r<rows ;r++) {
    for(unsigned int c=0; c<cols ;c++) {

      //make lowercase before adding
      std::string data = diceArray[r][c];
      std::transform(data.begin(), data.end(), data.begin(), ::tolower);
      this->board[r][c] = BoardNode( data );

      //this->board[r][c] = BoardNode( std::tolower(diceArray[r][c]) );
    }
  }

  //TEMPORARY TESTER FUNCTION TO DISPLAY BOARD IN TERMINAL OUT
  /*
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      std::cout << (board[i][j]).getFace();
    }
    std::cout << endl;
  }*/
}

void BogglePlayer::buildLexicon(const set<string>& word_list) {
  ;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
  return false;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
  return false;
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
  vector<int> journey = vector<int>();

  //if setBoard has not been called, return null vector
  if (board == nullptr) {
    return vector<int>();
  }

  //lower the input string
  std::string data = word_to_check;
  std::transform(data.begin(), data.end(), data.begin(), ::tolower);

  //vector<int> retV = vector<int>();

  //set all nodes on board to unvisited
  for(unsigned int r=0; r<height; r++) {
    for(unsigned int c=0; c<width; c++) {
      (this->board[r][c]).setVisited(false);
    }
  }

  //will check routes starting from every node (dice) on board
  for(unsigned int r=0; r<height; r++) {
    for(unsigned int c=0;c<width; c++) {
      bool flag = DFS(r,c,data, journey);

      //if flag true, found a path for string, return it's journey as int vector
      if (flag == true) {
        journey.insert(journey.begin(), r*width + c);
        return journey;
      }
    }
  }

  //if passed through without returning, no path found, return empty vector
  return vector<int>();
}

bool BogglePlayer::DFS(int ROW, int COL, std::string toCheck, vector<int> &journey) {

  //check to see if out of bounds (negative or more than width or height)
  if ( COL < 0 || COL >= width || ROW < 0 || ROW >= height) {
    return false;
  }

  //if already visited on this path, cannot be used again
  if ( (this->board[ROW][COL]).getVisited() == true) {
    return false;
  }

  //quick check to see if node(dice) has longer length than remaining string
  std::string thisFace = (this->board[ROW][COL]).getFace();
  if (thisFace.length() > toCheck.length() ) {
    return false;
  }

  //check to see if face equals next string to be check
  for (unsigned int i = 0; i < thisFace.length(); i++) {
    if (thisFace[i] != toCheck[i] ) {
      return false;
    }
  }

  //passed, so can erase segment just check from remaining string
  toCheck.erase(0,thisFace.length());

  //if nothing left, string passed, this route works
  if (toCheck.empty() == true) {
    return true;
  }

  //otherwise, path might still be okay, continue checking
  else {
    (this->board[ROW][COL]).setVisited(true);
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
          bool result = DFS( ROW+i, COL+j, toCheck, journey);
          if (result == true) {
            journey.insert( journey.begin(), (ROW+i)*width + COL + j);
            return true;
          } 
      }
    }
  }

  //could not find route from this node, set to false (other path might still use it)
  (this->board[ROW][COL]).setVisited(false);
  return false;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
  ;
}


