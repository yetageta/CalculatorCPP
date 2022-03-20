#include <iostream>

#include "Lexer.h"
#include "Parser.h"
#include "main.h"

int main()
{
    std::string code;
    std::cin >> code;

    Lexer lex = Lexer();
    lex.ParseString(code);

    Parser parse = Parser();
    parse.SetTokens(lex.tokens);
    parse.ParseTokens();

    std::cout << "The solution to your calculation is: " << parse.result;
    std::cin >> code;
}
