#include "Parser.h"
#include <iostream>

std::list<Token*> GetTokensByType(std::list<Token>& tokens, TokenType type) {
	std::list<Token*> newList;
	for (auto& val : tokens) {
		if (val.type == type) {
			newList.push_back(&val);
		}
	}
	return newList;
}

int GetTokenOccurence(std::list<Token*> tokens, TokenType type) {
	int count = 0;
	for (auto& val : tokens) {
		if ((*val).type == type) {
			count += 1;
		}
	}
	return count;
}

int GetPositionOfToken(std::list<Token>& tokens, Token& searchToken) {
	int count = 0;
	for (auto& val : tokens) {
		if (&val == &searchToken) {
			return count;
		}
		count += 1;
	}
	return -1;
}

void Parser::ParseTokens() {
	std::list<Token*> LeftPars = GetTokensByType(tokens, TokenType::LPAREN);
	std::list<Token*> RightPars = GetTokensByType(tokens, TokenType::RPAREN);

	int leftParCount = LeftPars.size();
	int rightParCount = RightPars.size();

	if (leftParCount != rightParCount) {
		std::cout << "ERROR: Unequal number of parentheses.";
		return;
	}

	if (leftParCount > 0) {
		ParseParentheses();
	}

	int length = GetPositionOfToken(tokens, *std::next(tokens.end(), -1));
	Token newToken = EvaluateExpression(0, length);
	result = std::stod(newToken.content);
}

void Parser::ParseParentheses()
{
	std::list<Token*> LeftPars = GetTokensByType(tokens, TokenType::LPAREN);
	std::list<Token*> RightPars = GetTokensByType(tokens, TokenType::RPAREN);

	int countLeft = 0, countRight = 0;
	int positionStart = 0, positionEnd = 0;


	int globalIterator = 0;
	for (auto& token : tokens) {
		if (token.type == TokenType::LPAREN) {
			countLeft += 1;
		}

		if (token.type == TokenType::RPAREN) {
			countRight += 1;
		}

		if (countLeft == countRight && countLeft > 0) {

			positionStart = GetPositionOfToken(tokens, **std::next(LeftPars.begin(), countLeft-1));
			positionEnd = GetPositionOfToken(tokens, **RightPars.begin());

			Token newToken = EvaluateExpression(positionStart + 1, positionEnd - 1);

			std::list<Token> newTokenList;
			Token* newTokenInNewList = nullptr;

			int iterator = 0;
			int newTokenIndex = 0;

			for (std::list<Token>::iterator i = tokens.begin(); i != tokens.end(); i++)
			{
				if (iterator < positionStart || iterator > positionEnd) {
					newTokenList.push_back(*i);
				}
				if (iterator == positionStart) {
					newTokenList.push_back(*i);
					newTokenInNewList = &newTokenList.back();
				}
				iterator += 1;
			}

			(*newTokenInNewList).type = TokenType::FLOAT;
			(*newTokenInNewList).content = newToken.content;

			tokens = newTokenList;

			break;
		}
		globalIterator += 1;
	}

	if (countLeft > 0) {
		ParseParentheses();
	}
}

bool IsNumberType(std::list<Token*>::iterator token) {
	if ((*token)->type == TokenType::FLOAT || (*token)->type == TokenType::INTEGER) {
		return true;
	}
	return false;
}

bool IsValidMethod(std::list<Token*>::iterator token) {
	if ((*token)->type == TokenType::MULTIPLICATION || (*token)->type == TokenType::DIVISION || (*token)->type == TokenType::PLUS || (*token)->type == TokenType::MINUS) {
		return true;
	}
	return false;
}

Token Parser::EvaluateExpression(int start, int end) {
	std::list<Token*> resultList;

	int resultNumber = 0;

	int iteration = 0;
	for (auto& token : tokens) {
		if (iteration >= start && iteration <= end) {
			resultList.push_back(&token);
		}
		iteration += 1;
	}

	bool orderOfOperationsDone = false;

	std::list<Token*>::iterator lastElement;
	std::list<Token*>::iterator nextElement;

	for (std::list<Token*>::iterator i = resultList.begin(); i != resultList.end();i++)
	{
		if (IsValidMethod(i)) {
			lastElement = std::prev(i);
			nextElement = std::next(i);

			if (lastElement == resultList.end() || nextElement == resultList.end()) {
				continue;
			}

			if (!IsNumberType(lastElement) || !IsNumberType(nextElement)) {
				continue;
			}

			int size1 = GetTokenOccurence(resultList, TokenType::MULTIPLICATION);
			int size2 = GetTokenOccurence(resultList, TokenType::DIVISION);

			if (size1 + size2 == 0) {
				orderOfOperationsDone = true;
			}

			double val1 = (double)std::stof((*lastElement)->content);
			double val2 = (double)std::stof((*nextElement)->content);

			if ((*i)->type == TokenType::MULTIPLICATION) {
				(*i)->content = std::to_string(val1 * val2);
			}
			else if ((*i)->type == TokenType::DIVISION) {
				(*i)->content = std::to_string(val1 / val2);
			}

			if ((*i)->type == TokenType::PLUS) {
				if (!orderOfOperationsDone) continue;

				(*i)->content = std::to_string(val1 + val2);
			}
			if ((*i)->type == TokenType::MINUS) {
				if (!orderOfOperationsDone) continue;

				(*i)->content = std::to_string(val1 - val2);
			}

			(*i)->type = TokenType::FLOAT;
			i = resultList.erase(lastElement);
			i = resultList.erase(nextElement);
			i = resultList.begin();
		}
	}

	Token newToken = {};
	newToken.type = TokenType::FLOAT;
	newToken.content = (*resultList.begin())->content;
	return newToken;
}

Token Parser::ParseTokenSlice(std::list<Token> tokens)
{
	return Token();
}
