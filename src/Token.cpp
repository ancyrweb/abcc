#include "Token.h"

Token::Token(
  TokenType type, 
  std::string lexeme,
  int line, 
  int start, 
  int end) : 
  _type(type),
  _lexeme(lexeme),
  _line(line),
  _start(start), 
  _end(end) {

}

TokenType Token::getType() {
  return _type;
}

std::string Token::getLexeme() {
  return _lexeme;
}

int Token::getLine() {
  return _line;
}

int Token::getStart() {
  return _start;
}

int Token::getEnd() {
  return _end;
}