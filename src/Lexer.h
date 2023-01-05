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
	void keywordsOrIdentifier(std::string names[], TokenType tokenTypes[]);
	void stringLiteral();
	void numberLiteral();
	void identifier();

	// Utils
	// TODO most of them can be turned into macros
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

	// Source file being lexed
	std::string _source; 

	// Stateful, current line
	unsigned int _line;

	// Position in source where we started to read from
	unsigned int _start;

	// Position in source where we are currently
	unsigned int _current;

	// List of tokens processed until now
	std::vector<Token> _tokens;
};

#endif //ABCC_LEXER_H
