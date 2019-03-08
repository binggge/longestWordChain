#include "Core.h"
#include <iostream>
#include <string.h>

Core::Core()
{
}


Core::~Core()
{
}

int Core::create_map(char *words[], int len) {
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
			wordNode[pos].selfLoop = false;
			if (startChar == endChar) wordNode[pos].selfLoop = true;
			pos++;
		}
	}
	// update charNode
	for (int i = 0; i < 26; i++) {
		charNode[i].endChar = (char)(i + 'a');
		charNode[i].selfLoop = false;
		charNode[i].distanceToTail = -1000;
		for (int &j : charNode[i].reachableChar) {
			j = 0;
		}
	}
	for (int i = 0; i < pos; i++) {
		if (wordNode[i].selfLoop) {
			charNode[wordNode[i].endChar - 'a'].selfLoop = true;
		}
		else {
			charNode[wordNode[i].endChar - 'a'].reachableChar[wordNode[i].startChar - 'a'] = 1;
		}
	}
	return pos;
}

void Core::get_tails(int wnLen, char *retTails) {
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

void Core::bfs_gcw_no_r(char startTail) {
	int head = 0, tail = 0;
	int currDist = 0;
	// init startup
	bfsQueue[0].itemChar = startTail;
	bfsQueue[0].currDist = 0;
	tail++;
	while (head != tail) {
		//fetch from head
		char currChar = bfsQueue[head].itemChar;
		currDist = bfsQueue[head].currDist;
		head++;
		// update distance
		printf("head%d tail%d\n", head, tail);
		if (charNode[currChar - 'a'].selfLoop) {
			currDist += 1;
		}

		if (currDist > charNode[currChar - 'a'].distanceToTail) {
			charNode[currChar - 'a'].distanceToTail = currDist;
		}
		else {
			continue;
		}

		currDist = currDist + 1;

		// add queue
		for (int i = 0; i < 26; i++) {
			if (charNode[currChar - 'a'].reachableChar[i] == 1) {
				bfsQueue[tail].itemChar = (char)(i + 'a');
				bfsQueue[tail].currDist = currDist;
				tail++;
			}
		}
	}
}
void Core::bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail) {
	//update result
	int currentDist = maxi;
	char currentChar = maxc;
	int resultPos = 0;
	while (currentChar != tail) {
		if (charNode[currentChar - 'a'].selfLoop) {
			// have self loop
			for (int k = 0; k < wnLen; k++) {
				if (wordNode[k].startChar == currentChar && wordNode[k].endChar == currentChar) {
					result[resultPos] = wordNode[k].word;
					resultPos++;
					currentDist--;
					break;
				}
			}
		}
		// now move maxc to next char
		for (int k = 0; k < wnLen; k++) {
			if (wordNode[k].startChar == currentChar && charNode[wordNode[k].endChar - 'a'].distanceToTail == currentDist - 1) {
				result[resultPos] = wordNode[k].word;
				resultPos++;
				currentChar = wordNode[k].endChar;
				currentDist--;
				break;
			}
		}
	}
	// add the last one
	if (charNode[currentChar - 'a'].selfLoop) {
		// have self loop
		for (int k = 0; k < wnLen; k++) {
			if (wordNode[k].startChar == currentChar && wordNode[k].endChar == currentChar) {
				result[resultPos] = wordNode[k].word;
				resultPos++;
				break;
			}
		}
	}
}
int Core::create_dfs_map(char * words[], int len) {
	// Notice The map is reversed
	int wordSidePos = 0;
	for (int i = 0; i < 26; i++) {
		mapNode[i].currentChar = (char)(i + 'a');
	}
	for (int i = 0; i < len; i++) {
		char * currentWord = words[i];
		//add new side
		wordSide[wordSidePos].startChar = currentWord[0];
		wordSide[wordSidePos].endChar = currentWord[strlen(currentWord) - 1];
		wordSide[wordSidePos].word = currentWord;
		wordSide[wordSidePos].isVisited = false;
		wordSidePos++;
		// add side to the node
		mapNode[currentWord[0] - 'a'].outDegree += 1;
		mapNode[currentWord[strlen(currentWord) - 1] - 'a'].inDegree += 1;
		mapNode[currentWord[strlen(currentWord) - 1] - 'a'].nChar[mapNode[currentWord[strlen(currentWord) - 1] - 'a'].ncPos].nextChar = currentWord[0];
		mapNode[currentWord[strlen(currentWord) - 1] - 'a'].nChar[mapNode[currentWord[strlen(currentWord) - 1] - 'a'].ncPos].wsPointer = wordSidePos - 1;
		mapNode[currentWord[strlen(currentWord) - 1] - 'a'].ncPos++;

	}
	return wordSidePos;
}
void Core::get_tail_dfs(char* returnTails) {
	int alpList[26];
	for (int i = 0; i < 26; i++) {
		alpList[i] = mapNode[i].inDegree - mapNode[i].outDegree;
	}
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] >= 0) {
			returnTails[pos] = (char)(i + 'a');
			pos++;
		}
	}
	returnTails[pos] = '\0';
}
void Core::dfs_gcw_r(int depth, char currentChar, int route[], char head) {
	
	if (depth > maximumLength.length) {
		// more deep, update
		if (head == 0) {
			maximumLength.length = depth;
			memcpy(maximumLength.route, route, depth * sizeof(int));
		}
		else {
			if (currentChar == head) {
				maximumLength.length = depth;
				memcpy(maximumLength.route, route, depth * sizeof(int));
			}
		}

	}
	// visit next node
	for (int i = 0; i < mapNode[currentChar - 'a'].ncPos; i++) {
		if (wordSide[mapNode[currentChar - 'a'].nChar[i].wsPointer].isVisited) {
			continue;
		}
		// enter next
		route[depth] = mapNode[currentChar - 'a'].nChar[i].wsPointer;
		depth += 1;
		wordSide[mapNode[currentChar - 'a'].nChar[i].wsPointer].isVisited = true;
		//printf("%d %d %d\n", depth,i, mapNode[currentChar - 'a'].ncPos);
		dfs_gcw_r(depth, mapNode[currentChar - 'a'].nChar[i].nextChar, route, head);
		// go out
		wordSide[mapNode[currentChar - 'a'].nChar[i].wsPointer].isVisited = false;
		depth -= 1;

	}
}
void Core::dfs_get_result(char * result[]) {
	for (int i = 0; i < maximumLength.length; i++) {
		int pointer = maximumLength.route[maximumLength.length - i - 1];
		result[i] = wordSide[pointer].word;
	}
}
int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	int wnLen = 0;
	if (!enable_loop) {
		// no loop
		wnLen = create_map(words, len);
		// find the tails to run bfs
		char resultTails[27]; // all possibility of tails
		if (tail == 0) {
			get_tails(wnLen, resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}

		int cl = 0; // a save of current longest path
		for (int i = 0; i < strlen(resultTails); i++) {
			bfs_gcw_no_r(resultTails[i]);
			int maxi = -1; char maxc = head;
			if (head == 0) {
				for (int j = 0; j < 26; j++) {
					if (charNode[j].distanceToTail > maxi) {
						maxi = charNode[j].distanceToTail;
						maxc = charNode[j].endChar;
					}
				}
			}
			else {
				maxi = charNode[head - 'a'].distanceToTail;
				maxc = head;
			}

			//get max
			if (maxi > cl) {
				cl = maxi;
				//more bigger
				bfs_get_result(result, wnLen, maxi, maxc, resultTails[i]);
			}
		}

	}
	else {
		// -r==True
		// use DFS for no faster algorithm imaginable currently
		wnLen = create_dfs_map(words, len);
		// find the tails to run bfs
		char resultTails[27]; // all possibility of tails
		if (tail == 0) {
			get_tail_dfs(resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}
		printf("%s\n", resultTails);
		for (int i = 0; i < strlen(resultTails); i++) {
			printf("%d\n", i);
			int route[10000];
			dfs_gcw_r(0, resultTails[i], route, head);
		}
		
		dfs_get_result(result);
	}
	// Debug Use
	for (int i = 0; i < 10; i++) {
		printf("%s\n", result[i]);
	}
	return 0;
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	return 0;
}
