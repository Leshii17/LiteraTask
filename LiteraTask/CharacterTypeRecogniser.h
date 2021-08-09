#pragma once

enum class CharType
{
	kLetter,
	kDigit,
	kSymbol,
};

class CharacterTypeRecogniser
{
public:
	static CharType RecogniseCharType(char ch);
	static bool isDigit(char ch);
	static bool isLetter(char ch);
	static bool isCapitalLetter(char ch);
	static bool isControlSymbol(char ch);
private:
	CharacterTypeRecogniser();
};

