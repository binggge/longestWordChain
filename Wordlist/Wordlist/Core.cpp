#include "Core.h"
#include <iostream>
#include <string.h>

Core::Core()
{
}


Core::~Core()
{
}
void Core::roundTest(char * words[], int len) {
	// �ж�words��û�л����л�throw exception������û��-r������
	// ʹ������ɾ��
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
			throw "Find a loop but no -r";
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
	if (flag) throw "Find a loop but no -r";
}
int Core::create_map(char *words[], int len) {
	// ����BFSͼ���������ӣ����رߵ����ֻ����һ��������ߵ�wordNode���㵽charnode�������ܱ������ر���һ����
	// ���Ž�ͼ�������죬DFSҲһ����ԭ��δ֪
	int pos = 0;
	for (int i = 0; i < len; i++) {//�������е���
		char *currentWord;//��ǰ����
		char startChar, endChar;//��ǰ������β��ĸ
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

int Core::createMapChar(char * words[], int len)
{
	int wordNum = 0;
	for (int i = 0; i < len; i++)
	{
		char *currentWord;//��ǰ����
		char startChar, endChar;//��ǰ������β��ĸ
		int curlen;
		
		currentWord = words[i];
		curlen = strlen(currentWord);
		startChar = currentWord[0];
		endChar = currentWord[strlen(currentWord) - 1];
		bool flag = false;
		for (int j = 0; j < wordNum; j++) {
			if (wordNode[j].startChar == startChar && wordNode[j].endChar == endChar) {
				if (strlen(wordNode[j].word) < curlen)
				{
					wordNode[j].word = currentWord;
				}
				flag = true;
				break;
			}
		}
		if (!flag) {
			wordNode[wordNum].startChar = startChar;
			wordNode[wordNum].endChar = endChar;
			wordNode[wordNum].word = currentWord;
			if (startChar == endChar) 
				wordNode[wordNum].selfLoop = true;
			else
				wordNode[wordNum].selfLoop = false;
			wordNum++;
		}
	}

	return wordNum;
}

void Core::get_tails(int wnLen, char *retTails) {
	// �õ�BFS�������ܵ�������ʼ�ڵ㣬��Ϊ��Щ�������ǵ����������յ㣬���͸��Ӷȡ�
	// ��������retTails
	int alpList[26];
	for (int &i : alpList) {
		i = -10000000;
	}
	for (int i = 0; i < wnLen; i++) {
		alpList[wordNode[i].endChar - 'a'] = 0;

	}//���п���Ϊ��β����ĸ����
	for (int i = 0; i < wnLen; i++) {
		if (!wordNode[i].selfLoop) {
			alpList[wordNode[i].startChar - 'a'] += 1;//ͳ��ÿ����ĳ��ȣ������Ի����������
		}
	}
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] == 0) {
			retTails[pos] = (char)(i + 'a');
			pos++;
		}
	} // ͳ�����г���Ϊ0����ĸ�����ǿ�����β
	retTails[pos] = '\0';
}

void Core::bfs_gcw_no_r(char startTail) {
	// BFS����ÿ���㵽������������룬���������startTail����β��ͷ���������������µ�charNode��
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
		if (charNode[currChar - 'a'].selfLoop) {
			currDist += 1;
		} // ������Ի�һ���ߣ��൱�ھ���+1

		if (currDist > charNode[currChar - 'a'].distanceToTail) {
			charNode[currChar - 'a'].distanceToTail = currDist;
		}
		else {
			continue;
		} //����һ����ĸ�����η��ʵ�������ʵ�·���ĳ�С��֮ǰ�ı���ֵ���֦

		currDist = currDist + 1;

		// add queue
		for (int i = 0; i < 26; i++) {
			if (charNode[currChar - 'a'].reachableChar[i] == 1) {
				bfsQueue[tail].itemChar = (char)(i + 'a');
				bfsQueue[tail].currDist = currDist;
				tail++;
			} //������ߵ��Ľڵ㵽����
		}
	}
}
void Core::bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail) {
	// �Ӹ��¹���bfsͼ���ҳ���������µ�result��
	// maxc�ǵ�ǰ��ĸ��maxi�ǵ�ǰ����tail�ľ���
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
				} //��wordside���ҵ���Ӧ�ıߣ����
			}
		}//���Ի���maxi-2 ����-1
		// now move maxc to next char
		for (int k = 0; k < wnLen; k++) {
			if (wordNode[k].startChar == currentChar && charNode[wordNode[k].endChar - 'a'].distanceToTail == currentDist - 1) {
				result[resultPos] = wordNode[k].word;
				resultPos++;
				currentChar = wordNode[k].endChar;
				currentDist--;
				break;
			}//��wordside���ҵ���Ӧ�ıߣ����
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
		} //���һ����ĸ������Ի�Ҫ��һ�£�����while���߲���
	}
}
int Core::create_dfs_map(char * words[], int len) {
	//����DFSͼ��wordside�Ǳߣ�mapNode�ǽڵ㣬�����ܱ���
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
	// �õ�DFS�������ܵ�������ʼ�ڵ㡣��BFS��Ӧ�ò�ͨ�á�
	// ��������returnTails
	int alpList[26];
	for (int i = 0; i < 26; i++) {
		alpList[i] = mapNode[i].inDegree - mapNode[i].outDegree;
	} //ͳ��һ�������ȳ��Ȳ�
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] >= 0) {
			returnTails[pos] = (char)(i + 'a');
			pos++;
		} //���>=���Ȳſ����ǽ�β�ַ�
	}
	returnTails[pos] = '\0';
}
void Core::dfs_gcw_r(int depth, char currentChar, int route[], char head) {
	// DFS������ �����·����route ���Ž�ͼ������
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
		} //����ָ��head��������ߵ�head�Ÿ���·�����������ֻҪ·���䳤�͸���

	}
	// visit next node
	for (int i = 0; i < mapNode[currentChar - 'a'].ncPos; i++) {
		if (wordSide[mapNode[currentChar - 'a'].nChar[i].wsPointer].isVisited) {
			continue;
		}
		// enter next node
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
	// ��·�������ɵ����������浽result
	for (int i = 0; i < maximumLength.length; i++) {
		int pointer = maximumLength.route[maximumLength.length - i - 1];
		result[i] = wordSide[pointer].word;
	}
}
int route[10000];
int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	int wnLen = 0;
	if (!enable_loop) {
		roundTest(words, len);
		// no loop
		wnLen = create_map(words, len);
		// find the tails to run bfs
		char resultTails[27]; // all possibility of tails
		//���ǵ������Ǵ�β����ʼ�ģ�����Ҫѡ������ʵ�β����ĸ���е���ĸ��̫����ֱ����ȥ�����Ч��
		if (tail == 0) {//������β��ĸ
			get_tails(wnLen, resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}

		int cl = 0; // �����·������
		for (int i = 0; i < (int)strlen(resultTails); i++) { //���ڿ��ܵ�tail����һ������
			bfs_gcw_no_r(resultTails[i]);
			int maxi = -1; char maxc = head; // maxi����ǰβ��ĸ�·�����ȣ� maxc��ǰ·��������ĸ
			if (head == 0) {// ����������ĸ������Զ��
				for (int j = 0; j < 26; j++) {
					if (charNode[j].distanceToTail > maxi) {
						maxi = charNode[j].distanceToTail;
						maxc = charNode[j].endChar;
					}
				}
			}
			else {//ָ������ĸ
				maxi = charNode[head - 'a'].distanceToTail;
				maxc = head;
			}

			//get max
			if (maxi > cl) {
				cl = maxi;
				//more bigger, update
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
		if (tail == 0) {// ɾȥ�����ʵ�β��ͬ��
			get_tail_dfs(resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}
		printf("%s\n", resultTails);
		for (int i = 0; i < (int)strlen(resultTails); i++) { //�������ܵ�β
			printf("%d\n", i);
			
			dfs_gcw_r(0, resultTails[i], route, head);//��������ֱ�Ӱ�·�����浽���������µ�βʱ����Ҫ����ϴ��ߵ��·����
		}
		
		dfs_get_result(result);
	}
	int i = 0;
	while (result[i] != NULL) {//ͳ��result����
		i++;
	}
	if (i <= 1) { //�׳��쳣
		if (len == 0) {
			throw "Input file is empty";
		}
		else {
			throw "No chains found";
		}
	}
	return 0;
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	if (!enable_loop)
	{
		roundTest(words, len);
	}
	else
	{

	}
	int i = 0;
	while (result[i] != NULL) {//ͳ��result����
		i++;
	}
	if (i <= 1) { //�׳��쳣
		if (len == 0) {
			throw "Input file is empty";
		}
		else {
			throw "No chains found";
		}
	}
	return 0;
}
