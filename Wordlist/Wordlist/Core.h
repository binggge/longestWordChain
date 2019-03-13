#pragma once
class Core
{
public:
	Core();
	~Core();
	
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
private:
	struct wordnode {
		char startChar='0';
		char endChar = '0';
		char *word= new char [10000];
		bool selfLoop=false;
	} wordNode[10000];
	//最大26*26条边

	struct charnode {
		char endChar = '0';
		int reachableChar[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		bool selfLoop=false;
		int distanceToTail = 0;
	} charNode[30];
	//26个字母
	int reachDistance[26][26] = { 0 };
	struct queueitem {
		char itemChar = '0';
		int currDist=0;
	} bfsQueue[20000]; //BFS队列
	struct wordside {
		char startChar = '0';
		char endChar = '0';
		char *word = new char[10000];
		bool isVisited = false;
	} wordSide[10000]; //DFS边
	struct dfsmapnode {
		char currentChar = '0';
		struct nc {
			char nextChar = '0'; //actually the previous char
			int wsPointer = 0;
		} nChar[1000];
		int ncPos = 0;
		int inDegree = 0;
		int outDegree = 0;
	} mapNode[30]; //DFS节点
	struct maximumlength {
		int length = 0;
		int * route=new int[10000];
	} maximumLength; //DFS最长路径
	int create_map(char *words[], int len);
	int createMapChar(char *words[], int len);
	void get_tails(int wnLen, char *retTails);
	void bfs_gcw_no_r(char startTail);
	void bfs_gcc_no_r(char startTail);
	void bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail);
	void char_bfs_get_result(char * result[], int wnLen, int maxi, char maxc, char tail);

	int create_dfs_map(char * words[], int len);
	void get_tail_dfs(char* returnTails);
	void dfs_gcw_r(int depth, char currentChar, int route[], char head);
	void dfs_get_result(char * result[]);
	void roundTest(char * words[], int len);
};

