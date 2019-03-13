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
	// 判断words有没有环，有环throw exception，用于没有-r的数据
	// 使用拓扑删点
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
	// 创建BFS图，反向链接，有重边的情况只保留一条，保存边到wordNode，点到charnode，返回总边数（重边算一条）
	// 倒着建图，搜索快，DFS也一样，原因未知
	int pos = 0;
	for (int i = 0; i < len; i++) {//遍历所有单词
		char *currentWord;//当前单词
		char startChar, endChar;//当前单词首尾字母
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
		char *currentWord;//当前单词
		char startChar, endChar;//当前单词首尾字母
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
	// 得到BFS搜索可能的所有起始节点，因为有些不可能是单词链起点或终点，降低复杂度。
	// 保存结果到retTails
	int alpList[26];
	for (int &i : alpList) {
		i = -10000000;
	}
	for (int i = 0; i < wnLen; i++) {
		alpList[wordNode[i].endChar - 'a'] = 0;

	}//所有可能为结尾的字母置零
	for (int i = 0; i < wnLen; i++) {
		if (!wordNode[i].selfLoop) {
			alpList[wordNode[i].startChar - 'a'] += 1;//统计每个点的出度，其中自环不计入出度
		}
	}
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] == 0) {
			retTails[pos] = (char)(i + 'a');
			pos++;
		}
	} // 统计所有出度为0的字母，它们可能是尾
	retTails[pos] = '\0';
}

void Core::bfs_gcw_no_r(char startTail) {
	// BFS更新每个点到搜索起点的最长距离，搜索起点是startTail（从尾往头倒序搜索），更新到charNode中
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
		} // 如果有自环一定走，相当于距离+1

		if (currDist > charNode[currChar - 'a'].distanceToTail) {
			charNode[currChar - 'a'].distanceToTail = currDist;
		}
		else {
			continue;
		} //对于一个字母如果多次访问到，后访问的路径的长小于之前的保存值则剪枝

		currDist = currDist + 1;

		// add queue
		for (int i = 0; i < 26; i++) {
			if (charNode[currChar - 'a'].reachableChar[i] == 1) {
				bfsQueue[tail].itemChar = (char)(i + 'a');
				bfsQueue[tail].currDist = currDist;
				tail++;
			} //添加能走到的节点到队里
		}
	}
}
void Core::bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail) {
	// 从更新过的bfs图中找出最长链，更新到result中
	// maxc是当前字母，maxi是当前距离tail的距离
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
				} //从wordside中找到对应的边，输出
			}
		}//有自环，maxi-2 其他-1
		// now move maxc to next char
		for (int k = 0; k < wnLen; k++) {
			if (wordNode[k].startChar == currentChar && charNode[wordNode[k].endChar - 'a'].distanceToTail == currentDist - 1) {
				result[resultPos] = wordNode[k].word;
				resultPos++;
				currentChar = wordNode[k].endChar;
				currentDist--;
				break;
			}//从wordside中找到对应的边，输出
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
		} //最后一个字母如果有自环要走一下，上面while里走不到
	}
}
int Core::create_dfs_map(char * words[], int len) {
	//创建DFS图，wordside是边，mapNode是节点，返回总边数
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
	// 得到DFS搜索可能的所有起始节点。和BFS的应该不通用。
	// 保存结果到returnTails
	int alpList[26];
	for (int i = 0; i < 26; i++) {
		alpList[i] = mapNode[i].inDegree - mapNode[i].outDegree;
	} //统计一个点的入度出度差
	int pos = 0;
	for (int i = 0; i < 26; i++) {
		if (alpList[i] >= 0) {
			returnTails[pos] = (char)(i + 'a');
			pos++;
		} //入读>=出度才可能是结尾字符
	}
	returnTails[pos] = '\0';
}
void Core::dfs_gcw_r(int depth, char currentChar, int route[], char head) {
	// DFS搜树， 保存最长路径到route 倒着建图倒着搜
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
		} //对于指定head的情况，走到head才更新路径，其他情况只要路径变长就更新

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
	// 把路径解析成单词链并保存到result
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
		//我们的搜索是从尾部开始的，所以要选择出合适的尾部字母，有的字母不太合适直接舍去，提高效率
		if (tail == 0) {//无限制尾字母
			get_tails(wnLen, resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}

		int cl = 0; // 保存最长路径长度
		for (int i = 0; i < (int)strlen(resultTails); i++) { //对于可能的tail遍历一遍搜索
			bfs_gcw_no_r(resultTails[i]);
			int maxi = -1; char maxc = head; // maxi：当前尾字母最长路径长度， maxc当前路径的首字母
			if (head == 0) {// 遍历所有字母，找最远的
				for (int j = 0; j < 26; j++) {
					if (charNode[j].distanceToTail > maxi) {
						maxi = charNode[j].distanceToTail;
						maxc = charNode[j].endChar;
					}
				}
			}
			else {//指定首字母
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
		if (tail == 0) {// 删去不合适的尾，同上
			get_tail_dfs(resultTails);
		}
		else {
			resultTails[0] = tail;
			resultTails[1] = '\0';
		}
		printf("%s\n", resultTails);
		for (int i = 0; i < (int)strlen(resultTails); i++) { //遍历可能的尾
			printf("%d\n", i);
			
			dfs_gcw_r(0, resultTails[i], route, head);//这里我们直接把路径保存到类变量里，走新的尾时不需要清除上次走的最长路径。
		}
		
		dfs_get_result(result);
	}
	int i = 0;
	while (result[i] != NULL) {//统计result长度
		i++;
	}
	if (i <= 1) { //抛出异常
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
	while (result[i] != NULL) {//统计result长度
		i++;
	}
	if (i <= 1) { //抛出异常
		if (len == 0) {
			throw "Input file is empty";
		}
		else {
			throw "No chains found";
		}
	}
	return 0;
}
