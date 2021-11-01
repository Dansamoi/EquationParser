#include "Token.h"

Token::~Token()
{
}

void Token::debugPrint()
{
	cout << "[" << mTypeStrings[mType] << "] " << mText << endl;
}
