#include "boggleplayer.h"
#include "boggleplayer.cpp"
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include "boggleutil.cpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {  
  BaseBogglePlayer * p = new BogglePlayer(); 

  string row0[] = {"l","P","e","R","T","H","L","I"};;
  string row1[] = {"o","w","F","D","R","E","elicopter","D"};
  string row2[] = {"helicopt","h","t","l","I","L","ights","o"};
  string row3[] = {"licopter","s","h","h","F","out","S","N"};
  string* board[] = {row0,row1,row2,row3};

  set<string> words;
  vector<int> locations;
  p->setBoard(4,8,board);    //<-------this is important
  std::vector<int>checkVector;

  set<string> lex;
  lex.insert("def");
  lex.insert("drew");
  lex.insert("fed");
  lex.insert("lop");
  lex.insert("how");
  lex.insert("HoPe");
  lex.insert("now");
  lex.insert("onus");

  lex.insert("showed");
  lex.insert("shower");
  lex.insert("unwed");
  lex.insert("snowed");
  lex.insert("plower");
  lex.insert("power");

  lex.insert("hello");
  lex.insert("hi");
//  lex.insert("hats");
  lex.insert("helicopter");
  lex.insert("soN");
  lex.insert("fire");
  lex.insert("son");
  lex.insert("fLiRT");  

  p->buildLexicon(lex);

  p->getAllValidWords(1,&words);
  if (words.size() == 0) {
    cout << "ERROR: all valid words is empty" << endl;
  }
  cout << "--------VALID WORDS--------" << endl;
  for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
    cout << *it << endl;
  };

  cout << "END" << endl;
  //delete p;
}

