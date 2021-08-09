#include "DocumentParser.h"
#include "CharacterTypeRecogniser.h"
#include <ppl.h>
#include <sstream>

DocumentParser::DocumentParser()
{	
}

bool DocumentParser::StartExtracting(Document& doc) const
{
	return doc.ExtractContent();
}

void DocumentParser::SplitIntoWords(const Document& doc)
{
	for (size_t i = 0; i < doc.DocContent().size(); i++) {
		std::stringstream tempStream;
		std::string word;
		tempStream << doc.DocContent()[i];
		while (tempStream.peek() != EOF) {
			char tempCh;
			tempStream >> tempCh;
			if (CharacterTypeRecogniser::RecogniseCharType(tempCh) == CharType::kSymbol) {
				if (!word.empty()) {
					mtx_.lock();
					wordStorage_.insert(word);
					mtx_.unlock();
					word.clear();
				}
			} else {
				mtx_.lock();
				charStorage_[tempCh] += 1;
				mtx_.unlock();
				word.push_back(tempCh);
			}
		}
		if (!word.empty()) {
			std::lock_guard<std::mutex> guard(mtx_);
			wordStorage_.insert(word);
		}
	}
} 

bool DocumentParser::StartParse(Document& doc1, Document& doc2)
{
	concurrency::parallel_invoke(
		[&]() {
			StartExtracting(doc1);
			SplitIntoWords(doc1);
		},
		[&]() {
			StartExtracting(doc2);
			SplitIntoWords(doc2);
		}
	);
	return true;
}

bool DocumentParser::StartObfuscating(const Document& srcDoc1, const Document& srcDoc2, Document& outputDoc1, Document& outputDoc2)
{
	obf_ = std::make_unique<Obfuscator>();
	obf_.get()->ObfuscateDoc(charStorage_, wordStorage_);
	concurrency::parallel_invoke(
		[&]() {
			outputDoc1.SaveObfuscatedDocument(CreateObfuscatedDocContent(obf_.get()->WordDictionary(), srcDoc1));
		},
		[&]() {
			outputDoc2.SaveObfuscatedDocument(CreateObfuscatedDocContent(obf_.get()->WordDictionary(), srcDoc2));
		}
	);

	return true;
}

const std::map<char, size_t> & DocumentParser::CharStorage() const
{
	return charStorage_;
}

const std::set<std::string> & DocumentParser::WordStorage() const
{
	return wordStorage_;
}

std::string DocumentParser::CreateObfuscatedDocContent(const std::map<std::string, std::string> & wordDictionary, const Document & srcDoc)
{
	std::string obfText;
	size_t cntrSymbolIter = 0;
	if (!srcDoc.isWordFirst_) {
		obfText += srcDoc.GetControlSymbols(cntrSymbolIter);
		cntrSymbolIter++;
	}
	for (size_t i = 0; i < srcDoc.docContent_.size(); i++) {
		auto item = srcDoc.docContent_[i];
		std::stringstream tempStream;
		std::string orgWord;
		std::string obfWord;
		tempStream << item;
		while (tempStream.peek() != EOF) {
			char tempCh;
			tempStream >> tempCh;
			if (CharacterTypeRecogniser::RecogniseCharType(tempCh) == CharType::kSymbol) {
				if (wordDictionary.count(orgWord)) {
					obfWord = wordDictionary.at(orgWord);
				}
				obfWord += tempCh;
				obfText += obfWord;
				orgWord.clear();
				obfWord.clear();
			} else {
				orgWord.push_back(tempCh);
			}
		}
		if (!orgWord.empty()) {
			obfText += wordDictionary.at(orgWord);
			AddCntrlSymbolToObfText(srcDoc, cntrSymbolIter, obfText);
		} else if (i != srcDoc.docContent_.size() - 1) {
			AddCntrlSymbolToObfText(srcDoc, cntrSymbolIter, obfText);
		}
	}
	return obfText;
}

void DocumentParser::AddCntrlSymbolToObfText(const Document & srcDoc, size_t & cntrSymbolIter, std::string & obfText)
{
	if (cntrSymbolIter < srcDoc.controlSymbols_.size()) {
		obfText += srcDoc.GetControlSymbols(cntrSymbolIter);
		cntrSymbolIter++;
	}
}






