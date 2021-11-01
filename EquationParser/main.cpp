#include "Data.h"
#include "Tokenizer.h"
#include "Parser.h"

int main(void) {
	string equation;
	getline(cin, equation);
	vector<Token> tokens = Tokenizer::parse(equation);

	for (auto token : tokens) {
		token.debugPrint();
	}

	Parser::parse(tokens);
	cout << tokens[0].mText;
	return 0;
}