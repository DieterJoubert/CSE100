#include "boggleplayer.cpp"
#include <stdlib.h>

using namespace std;

char randomLetter(){
	char randomLetter;
	// random var to determine if letter will be upper or lower case
	int caseDet = rand() % 2;
	if(caseDet == 0){
		randomLetter = (rand() % 26) + 65;
	}
	else{
		randomLetter = (rand % 26) + 97;
	}

	return randomLetter;
}

int main(int argc, char **argv){
	string * foo;
	int height;
		int width;

	if(argc!= 3){
		cerr << "Usage: ./testSetBoard [width (decimal number) 
			[hieght (decimal number)]" << endl;
		return 1;
	}
	else if( argc < 3){
		height = 3;
		width = 3;
	}
	else{
		height = argv[1];
		width = argv[2];
	}

	for(int i = 0; i < height; ++i){
		string * bar;
		for(int j = 0; j < width; ++i){
			bar[j] = randomLetter();
		}
		foo[i] = bar;
	}
}