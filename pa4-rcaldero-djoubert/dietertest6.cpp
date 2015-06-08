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
  BaseBogglePlayer * pLexOnly = new BogglePlayer(); 

  set<string> lex2;
  lex2.insert("oath");
  lex2.insert("powerful");
  lex2.insert("art");
  lex2.insert("rat");
  lex2.insert("tear");
  lex2.insert("train");
  lex2.insert("TeHrAn");
  lex2.insert("HEART");
  lex2.insert("HeArT");
  lex2.insert("HEART");
  lex2.insert("tIe");

  pLexOnly->buildLexicon(lex2);

  delete pLexOnly;
}

