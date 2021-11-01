#pragma once
#include "Data.h"
#include "Token.h"
class Tokenizer
{
public:
	static vector<Token> parse(string data);
	static void endToken(vector<Token>& tokens, Token& token);
};

