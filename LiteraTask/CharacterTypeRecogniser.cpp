#include "CharacterTypeRecogniser.h"

CharType CharacterTypeRecogniser::RecogniseCharType(char ch)
{
    if (isDigit(ch)) {
        return CharType::kDigit;
    }
    if (isLetter(ch)) {
        return CharType::kLetter;
    }
    return CharType::kSymbol;
}

bool CharacterTypeRecogniser::isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool CharacterTypeRecogniser::isLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z';
}

bool CharacterTypeRecogniser::isCapitalLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

// Returns true if parameter equals '\a', '\b', '\t', '\n', '\v', '\f', '\r' and Space
bool CharacterTypeRecogniser::isControlSymbol(char ch)
{
    return ch >= 7 && ch <= 13 || ch == 32;
}


