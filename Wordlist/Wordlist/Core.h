#pragma once
class Core
{
public:
	Core();
	~Core();
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};

