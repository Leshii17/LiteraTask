#include "Obfuscator.h"
#include "CharacterTypeRecogniser.h"
#include <ctime>

Obfuscator::Obfuscator()
{
}

void Obfuscator::ObfuscateDoc(const std::map<char, size_t> & charStorage, const std::set<std::string> & wordStorage)
{
	srand(time(0));
	ObfuscateCharsStorage(charStorage);
	ObfuscateWordsStorage(wordStorage);
}

const std::map<std::string, std::string> & Obfuscator::WordDictionary() const
{
	return wordDictionary_;
}

const std::map<char, std::vector<char>> & Obfuscator::CharDictionary() const
{
	return charDictionary_;
}

void Obfuscator::ObfuscateCharsStorage(const std::map<char, size_t> & charStorage)
{
	for (auto item : charStorage) {
		std::vector<char> tempVec(item.second);
		if (CharacterTypeRecogniser::isDigit(item.first)) {
			for (size_t i = 0; i < tempVec.size(); i++) {
				tempVec[i] = ObfuscateDigit(item.first);
			}
		}
		else {
			for (size_t i = 0; i < tempVec.size(); i++) {
				tempVec[i] = ObfuscateChar(item.first);
			}
		}
		charDictionary_[item.first] = tempVec;
	}
}

void Obfuscator::ObfuscateWordsStorage(const std::set<std::string>& wordStorage)
{
	for (auto word : wordStorage) {
		std::string tempWord;
		for (auto ch : word) {
			if (!charDictionary_.empty()) {
				int lastCh = charDictionary_[ch].size() - 1;
				tempWord.push_back(charDictionary_.at(ch)[lastCh]);
				charDictionary_[ch].pop_back();
			} else {
				throw "charDictionary is empty";
			}
		}
		wordDictionary_[word] = tempWord;
	}
}

char Obfuscator::ObfuscateDigit(char c)
{
	AssertDigitsHeapFilled(c);
	int obfDigitIndex = rand() % digitsHeap_.size();
	char ch = digitsHeap_[obfDigitIndex];
	digitsHeap_.clear();
	return ch;
}

char Obfuscator::ObfuscateChar(char c)
{
	if (CharacterTypeRecogniser::isCapitalLetter(c)) {
		AssertCapitalCharsHeapFilled(c);
		int obfCharIndex = rand() % capitalCharsHeap_.size();
		char tempCh = capitalCharsHeap_[obfCharIndex];
		capitalCharsHeap_.clear();
		return tempCh;
	} else {
		AssertSmallCharsHeapFilled(c);
		int obfCharIndex = rand() % smallCharsHeap_.size();
		char tempCh = smallCharsHeap_[obfCharIndex];
		smallCharsHeap_.clear();
		return tempCh;
	}
}

void Obfuscator::AssertCapitalCharsHeapFilled(char c)
{
	//Capitall chars from 'A'(65) to 'Z'(90)
	for (size_t i = 65; i < 91; i++) {
		if ((char)i != c) {
			capitalCharsHeap_.push_back(i);
		}
	}
}

void Obfuscator::AssertSmallCharsHeapFilled(char c)
{
	//Small chars from 'a'(97) to 'z'(122)
	for (size_t i = 97; i < 123; i++) {
		if ((char)i != c) {
			smallCharsHeap_.push_back(i);
		}
	}
}

void Obfuscator::AssertDigitsHeapFilled(char c)
{
	//Digits from '0'(48) to '9'(56)
	for (size_t i = 48; i < 57; i++) {
		if ((char)i != c) {
			digitsHeap_.push_back(i);
		}
	}
}
