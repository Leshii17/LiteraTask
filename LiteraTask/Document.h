#pragma once
#include <vector>
#include <fstream>

class Document
{
	friend class DocumentParser;
public:
	Document(const std::string& path);

	const std::vector<std::string> & DocContent() const;
	const std::string & SrcPath() const;

private:
	std::string srcPath_;
	std::vector<std::string> docContent_;
	std::vector<std::vector<char>> controlSymbols_;
	bool isWordFirst_ = true;

	bool ExtractContent();
	bool ExtractControlSymbols(std::ifstream & srcDoc);
	void SaveObfuscatedDocument(const std::string & obfContent);
	std::string GetControlSymbols(size_t iter) const;
};

