#pragma once
#include "Data.h"
#include "Token.h"
class Parser
{
public:
	static void parse(vector<Token>& tokens);
	static void parseBrackets(vector<Token>& tokens, vector<Token>::iterator begin);
	static void parsePM(vector<Token>& tokens, vector<Token>::iterator begin);
	static void parseMD(vector<Token>& tokens, vector<Token>::iterator begin);
};

