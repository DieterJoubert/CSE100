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

  string row0[] = {"h","i","b","l"};
  string row1[] = {"b","A","s","S"};
  string* board[] = {row0,row1};

  p->setBoard(2,4,board);

  vector<int> check = p->isOnBoard("bass");
  if(check.size() == 0) {
    std::cerr << "Could not find 'bass'" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;

  check = p->isOnBoard("bASs");
  if(check.size() == 0) {
    std::cerr << "Could not find 'bASs'" << std::endl;    
  }
  for (auto it = check.begin(); it != check.end(); ++it) {
    std::cout << *it;
    std::cout << " ";
  }
  std:: cout << std::endl;
  
  delete p;
}

