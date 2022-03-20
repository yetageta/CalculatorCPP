#pragma once
#include "main.h"

class Lexer
{
public:
	std::list<Token> tokens;
	void ParseString(std::string str);
	void InsertMultiplication();
	Token GetToken();
private:
	std::string input;
	int pos;
};

