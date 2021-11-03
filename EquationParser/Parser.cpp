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
			case '+':
				result = stod((mCurrentToken - 1)->mText) + stod((mCurrentToken + 1)->mText);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				needRemove = 1;
				break;
			case '-':
				result = stod((mCurrentToken - 1)->mText) - stod((mCurrentToken + 1)->mText);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				needRemove = 1;
				break;
			default:
				break;
			}
			if (needRemove) {
				tokens.erase(mCurrentToken + 2);
				tokens.erase(mCurrentToken + 1);
				needRemove = 0;
				//mEndToken -= 2;
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
	bool needRemove = 0;

	while (mCurrentToken != tokens.end() && mCurrentToken->mText[0] != ')') {
		if (mCurrentToken->mType == OPERATOR) {
			switch (mCurrentToken->mText[0])
			{
			case '*':
				result = stod((mCurrentToken - 1)->mText) * stod((mCurrentToken + 1)->mText);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				needRemove = 1;
				break;
			case '/':
				result = stod((mCurrentToken - 1)->mText) / stod((mCurrentToken + 1)->mText);
				mCurrentToken--;
				mCurrentToken->mText = to_string(result);
				needRemove = 1;
				break;
			default:
				break;
			}
			if (needRemove) {
				tokens.erase(mCurrentToken + 2);
				tokens.erase(mCurrentToken + 1);
				needRemove = 0;
			}
		}
		mCurrentToken++;
	}

	return;
}
