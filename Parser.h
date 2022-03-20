#pragma once
#include "main.h"

class Parser
{
public:
	std::list<Token> tokens;
	double result = 0;
	void SetTokens(std::list<Token> tkn) {
		tokens = tkn;
	};
	void Validation();
	void ParseParentheses();
	Token EvaluateExpression(int start, int end);
	void ParseTokens();
	int GetTokenPosition(Token &token);
	Token ParseTokenSlice(std::list<Token> tokens);
};

