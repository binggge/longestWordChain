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
	} bfsQueue[10000];
	struct wordside {
		char startChar;
		char endChar;
		char *word;
		bool isVisited = false;
	} wordSide[10000];
	struct dfsmapnode {
		char currentChar;
		struct nc {
			char nextChar; //actually the previous char
			int wsPointer;
		} nChar[1000];
		int ncPos = 0;
		int inDegree = 0;
		int outDegree = 0;
	} mapNode[30];
	struct maximumlength {
		int length = 0;
		int route[1000];
	} maximumLength;
	int create_map(char *words[], int len);
	void get_tails(int wnLen, char *retTails);
	void bfs_gcw_no_r(char startTail);
	void bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail);
	int create_dfs_map(char * words[], int len);
	void get_tail_dfs(char* returnTails);
	void dfs_gcw_r(int depth, char currentChar, int route[], char head);
	void dfs_get_result(char * result[]);
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};

