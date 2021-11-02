#include "Tokenizer.h"

vector<Token> Tokenizer::parse(string data)
{
	vector<Token> tokens;
	Token currentToken;

	for (auto ch : data) {
		switch (ch)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			switch (currentToken.mType) {
			case UNDEFINED:
				currentToken.mText.append(1, ch);
				currentToken.mType = NUMBER;
				break;
			case NUMBER:
				currentToken.mText.append(1, ch);
				break;
			case OPERATOR:
				endToken(tokens, currentToken);
				currentToken.mText.append(1, ch);
				currentToken.mType = NUMBER;
				break;
			}
			break;

		case '+': case '-': case '=': case '*': case '/': case '(': case ')':
			switch (currentToken.mType) {
			case UNDEFINED:
				currentToken.mText.append(1, ch);
				currentToken.mType = OPERATOR;
				break;
			case NUMBER:
				endToken(tokens, currentToken);
				currentToken.mText.append(1, ch);
				currentToken.mType = OPERATOR;
				break;
			case OPERATOR:
				endToken(tokens, currentToken);
				currentToken.mText.append(1, ch);
				currentToken.mType = OPERATOR;
				break;
			}
			break;
		case '.':
			switch (currentToken.mType) {
			case UNDEFINED:
				currentToken.mText.append(1, ch);
				currentToken.mType = NUMBER;
				break;
			case NUMBER:
				currentToken.mText.append(1, ch);
				break;
			case OPERATOR:
				endToken(tokens, currentToken);
				currentToken.mText.append(1, ch);
				currentToken.mType = NUMBER;
				break;
			}
			break;

		default:
			break;
		}
	}
	endToken(tokens, currentToken);

	return tokens;
}

void Tokenizer::endToken(vector<Token>& tokens, Token& token)
{
	tokens.push_back(token);
	token.mText = "";
	token.mType = UNDEFINED;
}
