#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Wordlist/Core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
char * words1[10000];
char * result1[10000];
int readFile1(char * path) {
	FILE  * fin;
	int err = fopen_s(&fin, path, "r");
	char currentChar;
	currentChar = (char)fgetc(fin);

	int wordPos = 0;
	while (currentChar != EOF) {
		if (isalpha(currentChar) != 0) {
			char * wordBuff = new char[1000];
			int wordBuffPos = 0;
			//printf("%c",currentChar);
			while (isalpha(currentChar) != 0) {
				wordBuff[wordBuffPos] = tolower(currentChar);
				wordBuffPos++;
				currentChar = (char)fgetc(fin);
			}
			wordBuff[wordBuffPos] = '\0';
			words1[wordPos] = wordBuff;
			wordPos++;
		}
		else {
			currentChar = (char)fgetc(fin);
		}
	}
	return wordPos;
}
namespace WordChainUnitTesr
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words1.txt");
			core->gen_chain_word(words1, len, result1, 0, 0, false);
			int len2 = readFile1("../WordChainUnitTesr/solution1.txt");
			Assert::AreEqual(4, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod2)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words1_1.txt");
			core->gen_chain_char(words1, len, result1, 0, 0, false);
			int len2 = readFile1("../WordChainUnitTesr/solution1_1.txt");
			Assert::AreEqual(3, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod3)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words2.txt");
			core->gen_chain_word(words1, len, result1, 0, 0, true);
			int len2 = readFile1("../WordChainUnitTesr/solution2.txt");
			Assert::AreEqual(4, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod4)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words2_1.txt");
			core->gen_chain_char(words1, len, result1, 0, 0, true);
			int len2 = readFile1("../WordChainUnitTesr/solution2_1.txt");
			Assert::AreEqual(3, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod5)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words3.txt");
			core->gen_chain_word(words1, len, result1, 'e', 0, false);
			int len2 = readFile1("../WordChainUnitTesr/solution3.txt");
			Assert::AreEqual(4, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod6)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words4.txt");
			core->gen_chain_word(words1, len, result1, 0, 'e', false);
			int len2 = readFile1("../WordChainUnitTesr/solution4.txt");
			Assert::AreEqual(4, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod7)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words5.txt");
			core->gen_chain_word(words1, len, result1, 'c', 'e', false);
			int len2 = readFile1("../WordChainUnitTesr/solution5.txt");
			Assert::AreEqual(2, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod8)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words6.txt");
			core->gen_chain_char(words1, len, result1, 'e', 'e', true);
			int len2 = readFile1("../WordChainUnitTesr/solution6.txt");
			Assert::AreEqual(3, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod9)
		{
			Core * core = new Core();
			int len = readFile1("../WordChainUnitTesr/words7.txt");
			core->gen_chain_word(words1, len, result1, 0, 0, false);
			int len2 = readFile1("../WordChainUnitTesr/solution7.txt");
			Assert::AreEqual(13, len2);
			for (int i = 0; i < len2; i++) {
				Assert::AreEqual(strcmp(result1[i], words1[i]), 0);
			}
			delete core;
		}
		TEST_METHOD(TestMethod10)
		{
			try {
				Core * core = new Core();
				int len = readFile1("../WordChainUnitTesr/words8.txt");
				core->gen_chain_word(words1, len, result1, 0, 0, false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
					Assert::AreEqual(strcmp(msg, "Find a loop but no -r"), 0);
			}
		}
		TEST_METHOD(TestMethod11)
		{
			try {
				Core * core = new Core();
				int len = readFile1("../WordChainUnitTesr/words9.txt");
				core->gen_chain_word(words1, len, result1, 0, 0, false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
				Assert::AreEqual(strcmp(msg, "Find a loop but no -r"), 0);
			}
		}
		TEST_METHOD(TestMethod12)
		{
			try {
				Core * core = new Core();
				int len = readFile1("../WordChainUnitTesr/words10.txt");
				core->gen_chain_word(words1, len, result1, 0, 0, false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
				Assert::AreEqual(strcmp(msg, "No chains found"), 0);
			}
		}
		TEST_METHOD(TestMethod13)
		{
			try {
				Core * core = new Core();
				int len = readFile1("../WordChainUnitTesr/words11.txt");
				core->gen_chain_word(words1, len, result1, 'e', 0, false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
				Assert::AreEqual(strcmp(msg, "No chains found"), 0);
			}
		}
		TEST_METHOD(TestMethod14)
		{
			try {
				Core * core = new Core();
				int len = readFile1("../WordChainUnitTesr/words12.txt");
				core->gen_chain_word(words1, len, result1, 0,'e', false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
				Assert::AreEqual(strcmp(msg, "No chains found"), 0);
			}
		}
		TEST_METHOD(TestMethod15)
		{
			try {
				Core * core = new Core();
				words1[0] = "";
				core->gen_chain_word(words1, 0, result1, 0, 'e', false);
				//RAISE EXCEPTION "Find a loop but no -r"
			}
			catch (const char* msg) {
				Assert::AreEqual(strcmp(msg, "Input file is empty"), 0);
			}
		}
	};
}