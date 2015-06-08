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

    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

    bool DFS(int x, int y, std::string toCheck, vector<int> &journey);
    void validSearch(int ROW, int COL, string soFar);

  //private:
    BoardNode ** board;
    MWTNode * lexRoot;
    MWTNode * curr;

    set<string> * myWords;
    //set<string> twoPrefixes;
    //set<string> threePrefixes;
    //set<string> fivePrefixes;
    unsigned int maxLength;
    unsigned int minLength;

    unsigned int width;
    unsigned int height;

};
#endif // BOGGLEPLAYER_H
