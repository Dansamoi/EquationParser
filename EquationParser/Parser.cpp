#include "Parser.h"

void Parser::parse(vector<Token>& tokens)
{
	vector<Token>::iterator mEndToken = tokens.end();
	vector<Token>::iterator mCurrentToken = tokens.begin();

	double result;
	bool needRemove = 0;

	while (mCurrentToken != mEndToken) {
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
				mEndToken = tokens.end();
			}
		}
		mCurrentToken++;
	}

	mEndToken = tokens.end();
	mCurrentToken = tokens.begin();

	while (mCurrentToken != mEndToken) {
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
				mEndToken = tokens.end();
			}
		}
		mCurrentToken++;
	}
	return;
}
