#include <iostream>
#include <fstream>
#include <ctype.h>
#include "core.h"

char *result[10000];
void error(int e) {
	if (e == 1) throw "missing arguments";
	if (e == 2) throw "duplicated read file";
	if (e == 3) throw "file not exist";
	if (e == 4) throw "duplicated -h";
	if (e == 5) throw "wrong -h";
	if (e == 6) throw "duplicated -t";
	if (e == 7) throw "wrong -t";
	if (e == 8) throw "duplicated -r";
	if (e == 9) throw "undefined error";
	if (e == 10) throw "no input file";
	if (e == 11) throw "has a circle while -r = false";
	if (e == 12) throw "no word link found";
}
char * words[10000];
int readFile(char * path) {
	std::ifstream fin;
	fin.open(path);
	char currentChar;
	currentChar = fin.get();
	int wordPos = 0;
	while (currentChar != EOF) {
		if (isalpha(currentChar) != 0) {
			char * wordBuff = new char[1000];
			int wordBuffPos = 0;
			//printf("%c",currentChar);
			while (isalpha(currentChar) != 0) {
				wordBuff[wordBuffPos] = tolower(currentChar);
				wordBuffPos++;
				currentChar = fin.get();
			}
			wordBuff[wordBuffPos] = '\0';
			words[wordPos] = wordBuff;
			wordPos++;
		}
		else {
			currentChar = fin.get();
		}
	}
	fin.close();
	return wordPos;
}

int main(int argc, char * argv[]) {
	try {
		// prase input
		if (argc <= 1) {
			error(1); //error: missing arguments
		}
		char head, tail;
		bool hasRound;
		head = 0; tail = 0; hasRound = false;
		int len = 0;
		int posInArgc = 1;
		char * currentWord;
		bool readAttributes[5]; // wchtr
		readAttributes[0] = false; readAttributes[1] = false; readAttributes[2] = false; readAttributes[3] = false; readAttributes[4] = false;
		while (posInArgc < argc) {
			currentWord = argv[posInArgc];
			if (strcmp(currentWord, "-w") == 0) {
				//read file
				posInArgc++;
				char * readPath = argv[posInArgc];
				posInArgc++;
				if (readAttributes[0] || readAttributes[1]) {
					error(2);//duplicated read file
				}
				readAttributes[0] = true;
				std::fstream _file;
				_file.open(readPath, std::ios::in);
				if (!_file) {
					error(3);//file not exist
				}
				len = readFile(readPath);
			}
			else if (strcmp(currentWord, "-c") == 0) {
				// -c
				//read file
				posInArgc++;
				char * readPath = argv[posInArgc];
				posInArgc++;
				if (readAttributes[0] || readAttributes[1]) {
					error(2);//duplicated read file
				}
				readAttributes[1] = true;
				std::fstream _file;
				_file.open(readPath, std::ios::in);
				if (!_file) {
					error(3);//file not exist
				}
				len = readFile(readPath);
			}
			else if (strcmp(currentWord, "-h") == 0) {
				posInArgc++;
				if (readAttributes[2]) {
					error(4); //duplicated -h
				}
				readAttributes[2] = true;
				if (strlen(argv[posInArgc]) == 1 && isalpha(argv[posInArgc][0]) != 0) {
					head = (char)(tolower(argv[posInArgc][0]));
				}
				else {
					error(5); //wrong -h
				}
				posInArgc++;
			}
			else if (strcmp(currentWord, "-t") == 0) {
				posInArgc++;
				if (readAttributes[3]) {
					error(6); //duplicated -t
				}
				readAttributes[3] = true;
				if (strlen(argv[posInArgc]) == 1 && isalpha(argv[posInArgc][0]) != 0) {
					tail = (char)(tolower(argv[posInArgc][0]));
				}
				else {
					error(7); //wrong -t
				}
				posInArgc++;
			}
			else if (strcmp(currentWord, "-r") == 0) {
				posInArgc++;
				if (readAttributes[4]) {
					error(8); //duplicated -r
				}
				readAttributes[4] = true;
				hasRound = true;
			}
			else {
				error(9); // undefined
			}
		}
		if (!readAttributes[0] && !readAttributes[1]) {
			error(10);
		}
		printf("%d", len);

		// ---------------------------------------------------------------------------------
		// main works
		Core * core = new Core();
		if (readAttributes[0]) {
			core->gen_chain_word(words, len, result, head, tail, hasRound);
		}
		else {
			core->gen_chain_char(words, len, result, head, tail, hasRound);
		}
		// ---------------------------------------------------------------------------------
		// output
		std::ofstream fout("solution.txt");
		int i = 0;
		while (result[i] != NULL) {
			i++;
		}
		if (i <= 1) {
			error(12);
		}
		i = 0;
		while (result[i] != NULL) {
			fout << result[i] << std::endl;
			i++;
		}
		fout.close();
	}
	catch (const char* msg) {
		printf("%s", msg);
	}
	catch (...) {
		printf("ERROR");
	}



	// do cover test
	/*core->gen_chain_word(words, len, result, head, tail, true);
	core->gen_chain_word(words, len, result, 'a', tail, true);
	core->gen_chain_word(words, len, result, head, 'z', true);
	core->gen_chain_word(words, len, result, 'a', tail, false);
	core->gen_chain_word(words, len, result, head, 'z', false);*/
	//getchar();
	return 0;
}