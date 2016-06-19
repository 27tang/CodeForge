#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const int size = 10000;


string array[4][4]={{"+1", "+i", "+j", "+k"},
					{"+i", "-1", "+k", "-j"},
					{"+j", "-k", "-1", "+i"},
					{"+k", "+j", "-i", "-1"}};


char multiplyChars(char a, char b){
	
}


int convertChar(char a){
	
}


int main(){

	ifstream fin;
	ofstream fout;
	char input[size] = {};
	int T = 0;
	
	fin.open("input.txt", ios::app);
	fin >> T;
	fin.ignore(size, '\n');

	if(fin.eof()){
		fin.close();
		fin.clear();
		return 0;
	}

	int L, X;

	for(int i = 1; i < T+1; ++i){
		fin >> L;
		fin.ignore(size, ' ');

		fin >> X;
		fin.ignore(size, '\n');

		fin.get(input, size, '\n');
		fin.ignore(size, '\n');

		char * string_input = new char[L*X]();
		for(int i = 0; i < X; ++i)
			strcat(string_input, input);

		
	
	
	
		delete [] string_input; 
	}


	return 0;
}
