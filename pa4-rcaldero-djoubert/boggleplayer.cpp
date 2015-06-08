#include "boggleplayer.h"
#include "boggleutil.h"
#include "baseboggleplayer.h"

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

BogglePlayer::BogglePlayer() {
  board = 0;
  boardSet = false;
  lexiconSet = false;
  lexRoot = 0;
  curr = 0;
}

BogglePlayer::~BogglePlayer() {
  if (board != 0) {
    destroyBoard();
  }
  if (lexRoot != 0) {
    delete lexRoot;
  }
  curr = nullptr;
}

/** Destructor helper method to iterate through all arrays in board and 
 *  successfuilly delete all elements/arrays
 */
void BogglePlayer::destroyBoard(){
  for(unsigned int i = 0; i < height; i++) {
    delete[] board[i];
  }
  delete[] board; 
}

/** Creates the array of arrays of nodes representing the board.
 * Takes as input the size of the array (rows and columns) and an array of array of
 * strings holding the strings of the dice
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {

  if (boardSet == true) {
    destroyBoard();
  }

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
    }
  }

  boardSet = true;
}

/** Takes a set of words and builds the lexicon dictionary
 * Uses the root pointer in this class as root of a multiway trie
 */
void BogglePlayer::buildLexicon(const set<string>& word_list) {
  if (lexiconSet == true) {
    delete lexRoot;
  }

  lexRoot = new MWTNode();
  maxLength = 0;

  MWTNode * cursor = 0;
  MWTNode * previous = 0;
  //iterate through list of input words
  for (set<string>::iterator it = word_list.begin(); it != word_list.end(); it++) {

    cursor = lexRoot;
    //transform each to lowercase to remain consistent throughout backend
    std::string word = *it;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    for (unsigned int i = 0; i < word.length(); i++) {       

      //transform char to ascii-97, so a=0,b=1,etc. to correspond to 
      //children array
      int ascii = ((int)word[i]) - 97;

      //if child at ascii-97 already exists, move cursor there
      if (cursor->children[ascii] != nullptr) {
        cursor = cursor->children[ascii];
      }

      //else make appropriate child and move cursor to it
      else {
        previous = cursor;
        cursor->children[ascii] = new MWTNode();
        cursor = cursor->children[ascii];
        cursor->parent = previous;
      }
    }

    //end of valid word, so set exists to true
    cursor->setExists(true);
    if (word.length() > maxLength) {
      maxLength = word.length();
    }
  }

  lexiconSet = true;
}

/** Returns all valid words of length equal to or greater than input min length.
 * Puts the valid words in the input point to a set of strings.
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {

  minLength = minimum_word_length;

  if( boardSet == false ){
    return false;
  }

  if (lexiconSet == false){
    return false;
  }

  //set all nodes on board to unvisited
  for(unsigned int r=0; r<height; r++) {
    for(unsigned int c=0; c<width; c++) {
      (this->board[r][c]).setVisited(false);
    }
  }

  //will check routes starting from every node (dice) on board
  for(unsigned int r=0; r<height; r++) {
    for(unsigned int c=0; c<width; c++) {
      string soFar = "";
      curr = lexRoot;
      validSearch(r,c,soFar,words);
    }
  }

  return true;
}

/** Searches for valid words from the input starting point.
 * Uses the function recursively to search from starting dice.
 * Uses pointer to dice path and pointer to lexicon, and traverses both,
 * turning back when lexicon path hits dead-end.
 */
void BogglePlayer::validSearch(int ROW, int COL, string soFar, set<string>* words) {

  //counter necessary for reading/checking dice of multiple chars
  int steps = 0;

  //quick check if word isn't already too long
  if (soFar.length() > maxLength) {
    return;
  }

  if ( COL < 0 || COL >= width || ROW < 0 || ROW >= height) {
    return;
  }

  if ( (this->board[ROW][COL]).getVisited() == true) {
    return;
  }

  //add diceface to string we're building on path
  string addStr = board[ROW][COL].getFace();

  //run lexicon down correct children as this diceface requires
  for (int k = 0; k < addStr.length(); k++) {
    int ascii = ((int)addStr[k]) - 97;

    //dead-end! run back as many times as have been run-down
    if (curr->children[ascii] == nullptr) {
      for (int z = 0; z < steps; z++) {
        curr = curr->parent;
      }
      return;
    }

    //otherwise, lexicon rundown successful, increment steps for backtracking
    else {
      steps++;
      curr = curr->children[ascii];
    }
  }

  soFar.append(addStr);

  //check if word meets min length requirement and is actual word in lexicon
  if (soFar.length() >= minLength && curr->getExists() == true) {
    words->insert(soFar);
  }

  board[ROW][COL].setVisited(true);

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      validSearch(ROW+i, COL+j, soFar, words);
    }
  }

  board[ROW][COL].setVisited(false);

  //traverse up in lexicon as many times as was traversed down
  for (int z = 0; z < steps; z++) {
    curr = curr->parent;
  }
  return;
}

/** For input string, checks if word can be found in lexicon by
 * running down multiway trie from root.
 */
bool BogglePlayer::isInLexicon(const string& word_to_check){
  //set cursor to lexicon's root
  MWTNode * cursor = lexRoot;
  string word = word_to_check;

  //safety catch: if word of length 0, return false
  if (word.length() == 0) {
    return false;
  }

  //make word lower case
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);

  for (unsigned int i = 0; i<word.length(); i++) {

    //transform char into ascii-97, where a=0,b=1,etc.
    int ascii = ((int)word[i]) - 97;

    //if next char's child for ascii does not exist, cannot exist, return false
    if (cursor->children[ascii] == nullptr) {
      return false;
    }

    //else move to children corresponding to ascii-97 value
    else {
      cursor = cursor->children[ascii];
    }
  }

  //if cursor's final position is valid word, return true
  if (cursor->getExists() == true) {
    return true;
  }
  else {
    return false;
  }
}

/** Checks if word can be found on boggle board by running from each
 * dice on board and doing a pathway search.
 */
vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
  vector<int> journey = vector<int>();

  //if setBoard has not been called, return null vector
  if (board == nullptr) {
    return vector<int>();
  }

  //lower the input string
  std::string data = word_to_check;
  std::transform(data.begin(), data.end(), data.begin(), ::tolower);

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

/** Funcion that is recursively used by isOnBoard to find path for input starting dice.
 * Will at end of recursion return true if word is found, false if not.
 */
bool BogglePlayer::DFS(int ROW, int COL, std::string toCheck, vector<int> &journey) {

  //check to see if out of bounds (negative or more than width or height)
  if ( COL < 0 || COL >= (int)width || ROW < 0 || ROW >= (int)height) {
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

  //could not find route from this node, set to false for other paths
  (this->board[ROW][COL]).setVisited(false);
  return false;
}

/** Creates custom board for testing purposes.
 */
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
  ;
}


