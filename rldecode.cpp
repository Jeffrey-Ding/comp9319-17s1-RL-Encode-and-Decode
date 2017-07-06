//============================================================================
// Name        : rldecode.cpp
// Author      : Jiarui Ding (z5045636)
// Version     :
// Copyright   : Your copyright notice
// Description : The following code is written for COMP9319 Assignment1
//============================================================================

#include <iostream>
#include <fstream>
# include <stdio.h>
# include <stdlib.h>

using namespace std;


// Function: 1 is returned if the first bit of a char is 0. //
int is_char (char c) {
	// doing AND with 1000 0000(bin)//
    return ((c & 128) == 0);
}


//=======================One Argument===========================//
void RLD1(char *in_file){

	ifstream fin(in_file, ios::binary);

	char symbol;

	// tmp to indicate the previous symbol (char / count)//
	char tmp;

	int count = -1;

	while(!fin.eof()){
		fin.read(&symbol, sizeof(char));

		// When reading a char//
		if (is_char(symbol) == 1){

			// if previous symbol is a count //
			if (is_char(tmp) == 0){
				cout  << '[' << count << ']';
				count = -1;
			}

			cout << symbol;
		}

		// When reading a count //
		else if (is_char(symbol) == 0){

			// if previous symbol is also a count //
			if (is_char(tmp) == 0){

				// concatenate 2 counts//
				count = (count << 7) | (symbol & 127);
			}

			// when a new count comes//
			else if(is_char(tmp) == 1){
				count = symbol & 127;
			}
		}

		tmp = symbol;


		// count for the last char //
		if(fin.peek() == EOF && count > -1){
			cout  << '[' << count << ']';
		}

	}

	fin.close();
}


//======================Two Arguments==========================//
void RLD2(char *in_file, char *out_file){

	// Open a read stream and a write stream //
	ifstream fin(in_file, ios::binary);
	ofstream fout(out_file,ios::out);

	char symbol;

	// tmp can be stored as either char or count)//
	char tmp;

	// Temporarily store previous char //
	char char_prev;

	int count = -1;

	while(!fin.eof()){
		fin.read(&symbol, sizeof(char));

		// When reading a char//
		if (is_char(symbol) == 1){

			// if previous symbol is a count //
			if (is_char(tmp) == 0){

				for (int i=0; i<count+3-1; i++){
					fout << char_prev;
				}
				count = -1;
			}

			fout << symbol;
			char_prev = symbol;

		}

		// When reading a count //
		else if (is_char(symbol) == 0){

			// if previous symbol is also a count //
			if (is_char(tmp) == 0){

				// concatenate 2 counts//
				count = (count << 7) | (symbol & 127);
			}

			// when a new count comes//
			else if(is_char(tmp) == 1){
				count = symbol & 127;
			}
		}

		tmp = symbol;


		// Use fin.peek() to print count for the last char //
		if(fin.peek() == EOF && count > -1){
			for (int i=0; i<count+3-1; i++){
				fout << char_prev;
			}
		}


	}

	fin.close();
	fout.close();

}


//========================Main=================================//
int main(int argc, char* argv[]) {


	// 1. Accept RLE_File and present on screen//
	if (argc == 2){
		RLD1(argv[1]);
	}
	// 2. Accept RLE_File and Write to OutputFile //
	else if (argc == 3){
		RLD2(argv[1], argv[2]);
	}
	//
	else {
		cout << "Error: Either one or two arguments are required" << endl;
	}

	return 0;
}
