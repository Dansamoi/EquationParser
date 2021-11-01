#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum Type {
	UNDEFINED,
	OPERATOR,
	NUMBER
};

static const char* mTypeStrings[] = {
	"NON",
	"OPERATOR",
	"NUMBER"
};
