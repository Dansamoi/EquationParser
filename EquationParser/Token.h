#pragma once
#include "Data.h"
class Token
{
public:
	Token(string text = "", Type type = UNDEFINED) : mType(type), mText(text) {};
	~Token();
	void debugPrint();

	string mText = "";
	enum Type mType;
};

