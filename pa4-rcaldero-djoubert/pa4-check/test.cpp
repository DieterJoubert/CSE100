/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iostream>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  string wordA("a");
  string wordX("x");
  lex.insert(wordA);
  lex.insert("z");
  string row0[] = {"h","e","L","x"};
  string row1[] = {"M","O","L","x"};
  string row2[] = {"w","o","W","x"};
  string row3[] = {"X","x","x","x"};  
  string* board[] = {row0,row1, row2, row3};
  set<string> words;
  vector<int> locations;

  p->setBoard(4,4,board);

  if(p->isOnBoard(wordX).size() == 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  vector<int> check = p->isOnBoard("low");
  if(check.size() == 0) {
    std::cerr << "Could not find 'low'" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;

  check = p->isOnBoard("how");
  if(check.size() == 0) {
    std::cerr << "Could not find 'low'" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;;

  if(p->isOnBoard("lLl").size() != 0) {
    std::cerr << "Found 'lll'" << std::endl;
  }

  check = p->isOnBoard("lowow");
  if(check.size() == 0) {
    std::cerr << "Could not find 'low'" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;

  check = p->isOnBoard("howllemwo");
  if(check.size() == 0) {
    std::cerr << "Could not find ''" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;;
  

  if(p->isOnBoard("lowowll").size() != 0) {
    std::cerr << "Found lowoll" << std::endl;
  }

  if(p->isOnBoard("he").size() == 0) {
    std::cerr << "Could not find 'he'" << std::endl;
  }

  if(p->isOnBoard("h").size() == 0) {
    std::cerr << "Could not find 'h'" << std::endl;
  }

  if(p->isOnBoard("hlww").size() != 0) {
    std::cerr << "Found hlww" << std::endl;
  }  

  delete p;
  return 0;

}
