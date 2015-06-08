#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main () {
  std::ifstream infile("input.txt");

  string a, b;
  int c, d;
  while (infile >> a >> b >> c >> d)
  {
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;    
  }
}