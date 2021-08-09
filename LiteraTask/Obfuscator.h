#pragma once
#include <map>
#include <string>
#include <vector>
#include <set>
#include "Document.h"

class Obfuscator
{
public:
	Obfuscator();

	void ObfuscateDoc(const std::map<char, size_t> & charStorage, const std::set<std::string> & wordStorage);
	const std::map<std::string, std::string> & WordDictionary() const;
	const std::map<char, std::vector<char>> & CharDictionary() const;

private:
	std::map<std::string, std::string> wordDictionary_;
	std::map<char, std::vector<char>> charDictionary_;
	std::vector<char> capitalCharsHeap_;
	std::vector<char> smallCharsHeap_;
	std::vector<char> digitsHeap_;

	void ObfuscateCharsStorage(const std::map<char, size_t> & charStorage);
	void ObfuscateWordsStorage(const std::set<std::string> & wordStorage);
	char ObfuscateDigit(char c);
	char ObfuscateChar(char c);
	void AssertCapitalCharsHeapFilled(char c);
	void AssertSmallCharsHeapFilled(char c);
	void AssertDigitsHeapFilled(char c);
};
