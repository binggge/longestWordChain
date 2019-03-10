#include <iostream>
#include <fstream>
#include <ctype.h>
#include "core.h"

char *result[10000];
void error(int e) {
	if (e == 1) printf("missing arguments");
	if (e == 2) printf("duplicated read file");
	if (e == 3) printf("file not exist");
	if (e == 4) printf("duplicated -h");
	if (e == 5) printf("wrong -h");
	if (e == 6) printf("duplicated -t");
	if (e == 7) printf("wrong -t");
	if (e == 8) printf("duplicated -r");
	if (e == 9) printf("undefined error");
	if (e == 10) printf("no input file");
	if (e == 11) printf("has a circle while -r = false");
	if (e == 12) printf("no word link found");
	exit(-1);
}
char * words[10000];
int readFile(char * path) {
	/*FILE  * fin = new FILE;
	int err;
	err= fopen_s(&fin,path, "r");
	char currentChar;
	currentChar = (char)fgetc(fin);*/
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
void roundTest(int len) {
	// test if has round
	int alp[26][26];
	int inDegree[26];
	for (auto &i : alp) {
		for (int &j : i) {
			j = 0;
		}
	}
	for (int &i : inDegree) {
		i = 0;
	}
	for (int i = 0; i < len; i++) {
		alp[words[i][0] - 'a'][words[i][strlen(words[i]) - 1] - 'a'] += 1;
	}
	for (int i = 0; i < 26; i++) {
		if (alp[i][i] >= 2) {
			error(11);
		}
	}
	for (int i = 0; i < 26; i++) {
		int sum = 0;
		for (int j = 0; j < 26; j++) {
			if (alp[j][i] != 0 && i != j) sum++;
		}
		inDegree[i] = sum;
	}
	int pos = -1;
	for (int i = 0; i < 26; i++) {
		if (inDegree[i] == 0) {
			pos = i;
			break;
		}
	}
	while (pos != -1) {
		// remove all pos
		inDegree[pos] = -1000;
		for (int i = 0; i < 26; i++) {
			if (alp[pos][i] != 0) {
				inDegree[i] -= 1;
			}
		}
		pos = -1;
		for (int i = 0; i < 26; i++) {
			if (inDegree[i] == 0) {
				pos = i;
				break;
			}
		}
	}
	bool flag = false;
	for (int i : inDegree) {
		if (i > 0) flag = true;
	}
	if (flag) error(11);
}
int main(int argc, char * argv[]) {

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
	Core * core= new Core();
	if (!hasRound) roundTest(len);
	if (readAttributes[0]) {
		//for (int i = 0; i < 50; i++) {
			core->gen_chain_word(words, len, result, head, tail, hasRound);
		//}
		
	}

	/*FILE * fout = new FILE;
	int erro = fopen_s(&fout, "solution.txt", "w");*/
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
		//fprintf(fout, "%s\n", result[i]);
		fout << result[i] << std::endl;
		i++;
	}
	fout.close();
	return 0;
}