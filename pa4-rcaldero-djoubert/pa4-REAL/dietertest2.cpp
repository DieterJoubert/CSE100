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

string row0[] = {"l","P","e","R"};
string row1[] = {"o","w","F","D"};
string row2[] = {"N","h","t","l"};
string row3[] = {"u","s","h","h"};
string* board[] = {row0,row1,row2,row3};

 

set<string> words;
vector<int> locations;


p->setBoard(4,4,board);    //<-------this is important
std::vector<int>checkVector;
checkVector = p->isOnBoard("TRIP");
if(checkVector.size()==4)
{
std::cout << "TRIP found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("mad");
if(checkVector.size()==3)
{
std::cout << "mad found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("Help");
if(checkVector.size()==4)
{
std::cout << "Help found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("lamE");
if(checkVector.size()==4)
{
std::cout << "lamE found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("dOmE");
if(checkVector.size()==4)
{
std::cout << "dOmE found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("FiRe");
if(checkVector.size()==4)
{
std::cout << "FiRe found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("flip");
if(checkVector.size()==4)
{
std::cout << "flip found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("real");
if(checkVector.size()==4)
{
std::cout << "real found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("ream");
if(checkVector.size()==4)
{
std::cout << "ream found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("HEAL");
if(checkVector.size()==4)
{
std::cout << "HEAL at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("had");
if(checkVector.size()==3)
{
std::cout << "had found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("hAm");
if(checkVector.size()==3)
{
std::cout << "hAm found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("son");
if(checkVector.size()==3)
{
std::cout << "son found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("LID");
if(checkVector.size()==3)
{
std::cout << "LID found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("dame");
if(checkVector.size()==4)
{
std::cout << "dame found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};
checkVector = p->isOnBoard("Team");
if(checkVector.size()==4)
{
std::cout << "Team found at: ";
for(unsigned int i = 0; i < checkVector.size(); i++)
{
std::cout<<checkVector.at(i)<<" ";
}
std::cout<<"\n";
};

}
