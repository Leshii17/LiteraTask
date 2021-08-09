#include "Document.h"
#include "CharacterTypeRecogniser.h"

Document::Document(const std::string& path)
{
	srcPath_ = path;
}

void Document::SaveObfuscatedDocument(const std::string & obfContent)
{
	std::ofstream outputDoc(srcPath_);
	if (!outputDoc.is_open()) {
		throw "Failed to open file" + srcPath_;
	}
	outputDoc << obfContent;
	outputDoc.close();
}

const std::vector<std::string> & Document::DocContent() const
{
	return docContent_;
}

const std::string & Document::SrcPath() const
{
	return srcPath_;
}

bool Document::ExtractContent()
{
	if (!docContent_.empty()) {
		return true;
	}
	std::ifstream srcDoc(srcPath_);
	if (!srcDoc.is_open()) {
		throw "Failed to open file" + srcPath_;
	}
	if (ExtractControlSymbols(srcDoc) && isWordFirst_) {
		isWordFirst_ = false;
	}
	std::string tmp;
	while (srcDoc >> tmp) {
		docContent_.push_back(tmp);
		ExtractControlSymbols(srcDoc);
	}
	srcDoc.close();
	return true;
}

bool Document::ExtractControlSymbols(std::ifstream & srcDoc)
{
	char tempCh = srcDoc.peek();
	std::vector<char> tempVec;
	bool tempBool = false;
	while (CharacterTypeRecogniser::isControlSymbol(tempCh)) {
		if (!tempBool) {
			tempBool = true;
		}
		srcDoc.get();
		tempVec.push_back(tempCh);
		tempCh = srcDoc.peek();
	}
	if (!tempVec.empty()) {
		controlSymbols_.push_back(tempVec);
		tempVec.clear();
	}
	return tempBool;
}

std::string Document::GetControlSymbols(size_t iter) const
{
	std::string result;
	for (auto symbol : controlSymbols_[iter]) {
		result += symbol;
	}
	return result;
}

