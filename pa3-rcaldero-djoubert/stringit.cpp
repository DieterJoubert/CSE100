#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main ()
{
  std::stringstream  stream("test string");
  std::string        oneWord;

  while(stream >> oneWord) { 
    cout << oneWord << endl;
  }

  return 0;
}


