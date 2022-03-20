#pragma once
#include <string>
#include <list>
#include <ctype.h>

enum TokenType {
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	INTEGER,
	FLOAT,
	LPAREN,
	RPAREN,
	EMPTY
};

struct Token {
	TokenType type;
	std::string content;
	int position;
};
