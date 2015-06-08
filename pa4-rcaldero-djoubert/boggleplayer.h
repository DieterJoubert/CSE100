#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"

#include <set>
#include <string>
#include <vector>

class BogglePlayer : public BaseBogglePlayer {

  public: 
    BogglePlayer();
    ~BogglePlayer();

    //FUNCTIONS INHERITED FROM BASEBOGGLEPLAYER
    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

    /** Funcion that is recursively used by isOnBoard to find path for input starting dice.
     * Will at end of recursion return true if word is found, false if not.
     */
    bool DFS(int x, int y, std::string toCheck, vector<int> &journey);

    /** Searches for valid words from the input starting point.
     * Uses the function recursively to search from starting dice.
     * Uses pointer to dice path and pointer to lexicon, and traverses both,
     * turning back when lexicon path hits dead-end.
     */
    void validSearch(int ROW, int COL, string soFar, set<string>*words);

    /** Destructor helper method to iterate through all arrays in board and 
     *  successfuilly delete all elements/arrays
     */
    void destroyBoard();

  private:
    //double pointer used to implement array of array of nodes representing boggle dice
    BoardNode ** board;

    //boggleplayer acts like lexicon class by holding pointer to root
    MWTNode * lexRoot;

    //helper pointer for running down lexicon during getAllValidWords
    MWTNode * curr;

    //max length of words in lexicon, useful for checking if word is on valid lex path
    unsigned int maxLength;

    //min length, set by user when calling getAllValidWords
    unsigned int minLength;

    //the width (# of rows) of the board
    unsigned int width;

    //the height (# of columns) of the board
    unsigned int height;

    //flag to check if board has been set
    bool boardSet;

    //flag to check if lexicon has been created
    bool lexiconSet;
};
#endif // BOGGLEPLAYER_H
