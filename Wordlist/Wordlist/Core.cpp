#include "Core.h"
#include <iostream>


Core::Core()
{
}


Core::~Core()
{
}

struct wordnode {
	char startChar;
	char endChar;
	char *word;
	int distanceToTail;
	bool selfLoop;
	char *path;
} wordNode[1000];

int createMap(char *words[], int len) {
	// create an acyclic map
	int pos = 0;
	for (int i = 0; i < len; i++) {
		char *currentWord;
		char startChar, endChar;
		currentWord = words[i];
		startChar = currentWord[0];
		endChar = currentWord[strlen(currentWord) - 1];
		bool flag = false;
		for (int j = 0; j < pos; j++) {
			if (wordNode[j].startChar == startChar && wordNode[j].endChar == endChar) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			// new node
			wordNode[pos].startChar = startChar;
			wordNode[pos].endChar = endChar;
			wordNode[pos].word = currentWord;
			wordNode[pos].distanceToTail = 0;
			wordNode[pos].selfLoop = false;
			if (startChar == endChar) wordNode[pos].selfLoop = true;
			pos++;
		}
	}
	return pos;
}

void getTails(int wnLen, char *retTails) {
	int alpList[26];
	for (int &i : alpList) {
		i = -10000000;
	}
	for (int i = 0; i < wnLen; i++) {
		alpList[wordNode[i].endChar - 'a'] = 0;

	}
	for (int i = 0; i < wnLen; i++) {
		if (!wordNode[i].selfLoop) {
			alpList[wordNode[i].startChar - 'a'] += 1;
		}
	}
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] == 0) {
			retTails[pos] = (char)(i + 'a');
			pos++;
		}
	}
	retTails[pos] = '\0';
}

int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	int wnLen = 0;
	if (!enable_loop) {
		// no loop
		wnLen = createMap(words, len);
	}
	char resultTails[26];
	if (tail == 0) {
		getTails(wnLen, resultTails);
	}
	else {
		resultTails[0] = tail;
		resultTails[1] = '\0';
	}
	return 0;
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	return 0;
}
