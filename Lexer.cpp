#include "Lexer.h"

bool isEmptySpace(char letter) {
	if (letter == ' ' || letter == '\n' || letter == '\r') {
		return true;
	}
	return false;
}

char nonStringTokens[6] = { '(', ')', '*', '/', '+', '-' };
bool isNonStringToken(char letter) {
	for (int i = 0; i < 6; i++) {
		if (nonStringTokens[i] == letter) {
			return true;
		}
	}
	return false;
}

void Lexer::ParseString(std::string str)
{
	input = str;

	while (bool running = true) {
		tokens.push_back(GetToken());
		pos += 1;
		if (pos > input.length() - 1) {
			running = false;
			break;
		}
	}

}

void Lexer::InsertMultiplication() {
	Token multiplicationToken = {};
	multiplicationToken.type = TokenType::MULTIPLICATION;
	tokens.push_back(multiplicationToken);
}

Token Lexer::GetToken()
{
	Token newToken = {};
	Token lastToken = {};
	std::list<Token>::iterator it;

	if (pos > 0) {
		lastToken = tokens.back();
		it = tokens.end();
	}

	switch (input[pos])
	{
	case '(': {
			if (lastToken.type == TokenType::FLOAT && pos > 0) {
				InsertMultiplication();
			};
			newToken.type = TokenType::LPAREN;
			break;
		}
	case ')': {
		newToken.type = TokenType::RPAREN; 

		it = std::prev(it, 2);

		if (lastToken.type == TokenType::FLOAT && it->type == TokenType::LPAREN) {
			newToken.type = TokenType::FLOAT;
			newToken.content = lastToken.content;

			tokens.erase(it);
			it = tokens.end();
			it = std::prev(it);
			tokens.erase(it);
		}

		break;
		}
	case '*': newToken.type = TokenType::MULTIPLICATION; break;
	case '/': newToken.type = TokenType::DIVISION; break;
	case '+': newToken.type = TokenType::PLUS; break;
	case '-': newToken.type = TokenType::MINUS; break;
	case ' ': newToken.type = TokenType::EMPTY; break;
	default:
		if (isdigit(input[pos])) {
			newToken.type = TokenType::FLOAT;
			newToken.content += input[pos];
			pos += 1;

			while (!isEmptySpace(input[pos]) && !isNonStringToken(input[pos]) && pos < input.length() - 1) {
				newToken.content += input[pos];
				if (input[pos] == '.') {
					newToken.type = TokenType::FLOAT;
				}

				pos += 1;
			}
			pos -= 1;
		}
	}

	return newToken;
}
