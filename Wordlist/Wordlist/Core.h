#pragma once
class Core
{
public:
	Core();
	~Core();
	struct wordnode {
		char startChar;
		char endChar;
		char *word;
		bool selfLoop;
	} wordNode[1000];

	struct charnode {
		char endChar;
		int reachableChar[26];
		bool selfLoop;
		int distanceToTail = 0;
	} charNode[30];
	struct queueitem {
		char itemChar;
		int currDist;
	} bfsQueue[100000];
	int createMap(char *words[], int len);
	void getTails(int wnLen, char *retTails);
	void bfs_gcw_no_r(char startTail);
	void bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail);
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};

