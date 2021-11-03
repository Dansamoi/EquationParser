#include "Data.h"
#include "Tokenizer.h"
#include "Parser.h"

int main(void) {
	//main menu

	string equation;
	cout << "Enter an equation:" << endl;
	getline(cin, equation);
	vector<Token> tokens = Tokenizer::parse(equation);

	//printing the tokens
	for (auto token : tokens) {
		token.debugPrint();
	}

	Parser::parse(tokens);
	cout << "The result is:" << endl;
	cout << tokens[0].mText;
	return 0;
}