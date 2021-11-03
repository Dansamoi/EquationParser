#include "Parser.h"

void Parser::parse(vector<Token>& tokens)
{
	/*
		parsing base data
	*/
	vector<Token>::iterator mEndToken = tokens.end();
	vector<Token>::iterator mCurrentToken = tokens.begin();

	double result;
	bool needRemove = 0;

	while (mCurrentToken != mEndToken) {
		if (mCurrentToken->mType == OPERATOR) {
			if (mCurrentToken->mText[0] == '(')
			{
				mCurrentToken = tokens.erase(mCurrentToken);
				parseBrackets(tokens, mCurrentToken);
				mEndToken = tokens.end();
			}
		}
		mCurrentToken++;
	}

	parseMD(tokens, tokens.begin());
	parsePM(tokens, tokens.begin());

	return;
}

void Parser::parseBrackets(vector<Token>& tokens, vector<Token>::iterator begin)
{
	/*
		parsing data inside brackets
	*/
	vector<Token>::iterator localBegin = begin;
	vector<Token>::iterator mEndToken = tokens.end();
	vector<Token>::iterator mCurrentToken = begin;

	while (mCurrentToken != mEndToken) {
		if (mCurrentToken->mType == OPERATOR) {
			if (mCurrentToken->mText[0] == '(')
			{
				mCurrentToken--;
				tokens.erase(mCurrentToken + 1);
				parseBrackets(tokens, mCurrentToken + 1);
				mEndToken = tokens.end();
			}
		}
		mCurrentToken++;
	}

	parseMD(tokens, localBegin);
	parsePM(tokens, localBegin);
	return;
}

void Parser::parsePM(vector<Token>& tokens, vector<Token>::iterator begin)
{
	/*
		plus minus control
	*/
	vector<Token>::iterator mCurrentToken = begin;

	double result;
	bool needRemove = 0;

	while (mCurrentToken != tokens.end() && mCurrentToken->mText[0] != ')') {
		if (mCurrentToken->mType == OPERATOR) {
			switch (mCurrentToken->mText[0])
			{
			case '+': case '-':
				result = resultOf(mCurrentToken);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				tokens.erase(mCurrentToken + 1);
				tokens.erase(mCurrentToken + 2);
				break;
			}
		}
		mCurrentToken++;
	}
	if (mCurrentToken != tokens.end() && mCurrentToken->mText[0] == ')') {
		tokens.erase(mCurrentToken);
	}
	return;
}

void Parser::parseMD(vector<Token>& tokens, vector<Token>::iterator begin)
{
	/*
		multiplication\division control
	*/
	vector<Token>::iterator mCurrentToken = begin;
	double result;

	while (mCurrentToken != tokens.end() && mCurrentToken->mText[0] != ')') {
		if (mCurrentToken->mType == OPERATOR) {
			switch (mCurrentToken->mText[0])
			{
			case '*': case '/':
				result = resultOf(mCurrentToken);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				tokens.erase(mCurrentToken + 1);
				tokens.erase(mCurrentToken + 2);
				break;
			}
		}
		mCurrentToken++;
	}

	return;
}

double Parser::resultOf(vector<Token>::iterator op)
{
	/*
		returns the result of the mathematical expression acording to the sign(operator)
	*/
	double result, first = stod((op - 1)->mText), second = stod((op + 1)->mText);
	switch (op->mText[0])
	{
	case '+':
		result = first + second;
		break;
	case '-':
		result = first - second;
		break;
	case '*':
		result = first * second;
		break;
	case '/':
		result = first / second;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
