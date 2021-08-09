#pragma once

#include "Document.h"
#include <map>
#include <set>
#include <mutex>
#include "Obfuscator.h"

class DocumentParser
{
public:
	DocumentParser();

	bool StartParse(Document & doc1, Document & doc2);
	bool StartObfuscating(const Document & srcDoc1, const Document & srcDoc2, Document& outputDoc1, Document& outputDoc2);
	const std::map<char, size_t> & CharStorage() const;
	const std::set<std::string> & WordStorage() const;
	bool StartExtracting(Document& doc) const;

private:
	std::map<char, size_t> charStorage_;
	std::set<std::string> wordStorage_;
	std::unique_ptr<Obfuscator> obf_;
	std::mutex mtx_;

	void SplitIntoWords(const Document& doc);
	std::string CreateObfuscatedDocContent(const std::map<std::string, std::string> & wordDictionary, const Document & srcDoc);
	void AddCntrlSymbolToObfText(const Document & srcDoc, size_t & cntrSymbolIter, std::string & obfText);
};




