//============================================================================
// Name        : rlencode.cpp
// Author      : Jiarui Ding (z5045636)
// Version     :
// Copyright   : Your copyright notice
// Description : The following code is written for COMP9319 Assignment
//============================================================================

#include <iostream>
#include <fstream>
# include <stdio.h>
# include <stdlib.h>

using namespace std;

// For text file <= 200MB, 4 bytes(segments) are sufficient to encode a maximum COUNT//
struct segment {
	int seg1;
	int seg2;
	int seg3;
	int seg4;
};

// Function: COUNT Encode //
segment Count_Encode(int num){

	segment S;

	// Boundaries to decide whether COUNT needs 1 more byte(segment) to encode//
	int seg1_bound = 127;		// 2^7 -1
	int seg2_bound = 16383;		// 2^7*2 -1
	int seg3_bound = 2097151;	// 2^7*3 -1
	int seg4_bound = 268435455; // 2^7*4 -1

	if (num <= seg1_bound){
		int seg1 = num | 128;
		S.seg1 = seg1; S.seg2 = -1; S.seg3 = -1; S.seg4 = -1;
	}
	else if (num > seg1_bound && num <= seg2_bound){
		int seg1 = ((num >> 7)&127)|128;
		int seg2 = (num & 127)|128;
		S.seg1 = seg1; S.seg2 = seg2; S.seg3 = -1; S.seg4 = -1;

	}
	else if (num > seg2_bound && num <= seg3_bound){
		int seg1 = ((num >> 14)&127)|128;
		int seg2 = ((num >> 7)&127)|128;
		int seg3 = (num & 127)|128;
		S.seg1 = seg1; S.seg2 = seg2; S.seg3 = seg3; S.seg4 = -1;

	}
	else if (num > seg3_bound && num <= seg4_bound){
		int seg1 = ((num >> 21)&127)|128;
		int seg2 = ((num >> 14)&127)|128;
		int seg3 = ((num >> 7)&127)|128;
		int seg4 = (num & 127)|128;
		S.seg1 = seg1; S.seg2 = seg2; S.seg3 = seg3; S.seg4 = seg4;
	}

	return S;
}


// ====================== One Argument: ========================//
void RLE1(char *f){

	ifstream fin(f, ios::in);

	// A counter to record the character duplicate times //
	int dup_char = 1;

	char symbol;
	char tmp;

	// Count for all characters except the last one //
	while(!fin.eof()){
		fin.read(&symbol, sizeof(char));

		// case: current char != previous char //
		if (symbol != tmp){

			if (dup_char > 2){
				cout << '[' << dup_char-3 << ']';
				cout << symbol;
			}

			else if (dup_char == 2){
				cout << tmp;
				cout << symbol;
			}

			else {
				cout << symbol;
			}

			dup_char = 1;
			tmp = symbol;
		}

		// case: current char = previous char //
		else if (symbol == tmp){
			dup_char ++;
		}


		//Count for the last character //
		if(fin.peek() == EOF && dup_char >= 3){
			cout << '[' << dup_char-3 << ']';
		}

		else if(fin.peek() == EOF && dup_char == 2){
			cout << symbol;
		}

	}

	fin.close();

}


//======================= Two arguments: =========================//
void RLE2(char *in_file, char *out_file){

	// Open a read stream //
	ifstream fin(in_file, ios::in);

	// Open a write stream //
	ofstream fout(out_file, ios::binary);

	int dup_char = 1;

	char symbol;
	char tmp;

	// Count for all characters except the last one //
	while(!fin.eof()){
		fin.read(&symbol, sizeof(char));

		// case: current char != previous char //
		if (symbol != tmp){

			if (dup_char > 2){
				int count =  dup_char-3;

				segment segs = Count_Encode(count);
				if (segs.seg1 > -1){
					fout.write((char*)(&segs.seg1), sizeof(char));
					if (segs.seg2 > -1){
						fout.write((char*)(&segs.seg2), sizeof(char));
						if (segs.seg3 > -1){
							fout.write((char*)(&segs.seg3), sizeof(char));
							if (segs.seg4 > -1){
								fout.write((char*)(&segs.seg4), sizeof(char));
							}
						}
					}
				}




				fout.write(&symbol, sizeof(char));
			}

			else if (dup_char == 2){
				fout.write(&tmp, sizeof(char));
				fout.write(&symbol, sizeof(char));
			}

			else {
				fout.write(&symbol, sizeof(char));
			}

			dup_char = 1;
			tmp = symbol;
		}

		// case: current char = previous char //
		else if (symbol == tmp){
			dup_char ++;
		}



		//Count for the last character //
		if(fin.peek() == EOF && dup_char >= 3){
			int count1  = dup_char-3;

			segment segs = Count_Encode(count1);
			if (segs.seg1 > -1){
				fout.write((char*)(&segs.seg1), sizeof(char));
				if (segs.seg2 > -1){
					fout.write((char*)(&segs.seg2), sizeof(char));
					if (segs.seg3 > -1){
						fout.write((char*)(&segs.seg3), sizeof(char));
						if (segs.seg4 > -1){
							fout.write((char*)(&segs.seg4), sizeof(char));
						}
					}
				}
			}
		}

		else if(fin.peek() == EOF && dup_char == 2){
			fout.write(&symbol, sizeof(char));
		}
	}

	fin.close();
	fout.close();
}



//========================Main==============================//
int main(int argc, char* argv[]) {

	// 1. Accept InputFile and present encoded on screen//
	if (argc == 2){
		RLE1(argv[1]);
	}
	// 2. Accept InputFile & Write to OutputFile //
	else if (argc == 3){
		RLE2(argv[1], argv[2]);
	}
	//
	else {
		cout << "Error: Either one or two arguments are required" << endl;
	}

	return 0;
}
