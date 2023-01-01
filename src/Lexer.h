#ifndef ABCC_LEXER_H
#define ABCC_LEXER_H

#include "Token.h"

#include <string>
#include <vector>

class Lexer {
public:
	Lexer();
	void scan(const std::string);
    
private:
	// Lexing
	void preproc();
	void preprocInclude();
	void keywordOrIdentifier(const std::string name, TokenType tokenType);
	void stringLiteral();
	void numberLiteral();
	void identifier();

	// Utils
	void skipWhitespaces();
	bool isAlpha(const char c);
	bool isDigit(const char c);
	bool isWhitespace(const char c);
	char advance();
	char peek();
	char peekNext();
	char peekAt(unsigned int index);
	void addToken(TokenType);
	bool isAtEnd();
	void reportError(std::string);

	// Debug
	void debugTokenString();

	std::string _source;
	unsigned int _line;
	unsigned int _start;
	unsigned int _current;
	std::vector<Token> _tokens;
};

#endif //ABCC_LEXER_H
