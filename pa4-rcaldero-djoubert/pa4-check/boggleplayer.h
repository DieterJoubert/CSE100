#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"

#include <vector>

class BogglePlayer : public BaseBogglePlayer {

  public: 
    BogglePlayer() { };
    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
    //~BaseBogglePlayer() {};
    bool DFS(int x, int y, std::string toCheck, vector<int> &journey);
    ~BogglePlayer(); //{ };

  //private:
    BoardNode ** board;

    unsigned int width;
    unsigned int height;

};
#endif // BOGGLEPLAYER_H