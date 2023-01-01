#include "Lexer.h"
#include "Debug.h"

#include <iostream>

Lexer::Lexer(): _line(0), _start(0), _current(0), _tokens() {

}

void Lexer::scan(const std::string source) {
  _source = source;

  while(!isAtEnd()) {
    skipWhitespaces();
    _start = _current;

    auto c = advance();
    switch (c) {
      case ';': { addToken(TokenType::SEMICOLON); break; }
      case '{': { addToken(TokenType::LEFT_BRACE); break; }
      case '}': { addToken(TokenType::RIGHT_BRACE); break; }
      case '(': { addToken(TokenType::LEFT_PAREN); break; }
      case ')': { addToken(TokenType::RIGHT_PAREN); break; }
      case '[': { addToken(TokenType::LEFT_BRACKET); break; }
      case ']': { addToken(TokenType::RIGHT_BRACKET); break; }
      case ',': { addToken(TokenType::COMMA); break; }
      case '.': { addToken(TokenType::DOT); break; }
      case '\\': { addToken(TokenType::BACK_SLASH); break; }
      case '#': {
        preproc();
        break;
      }
      case '<': {
        if (isAlpha(peek())) {
          preprocInclude();
        }
        break;
      }
      case 'a': {
        keywordOrIdentifier("auto", TokenType::AUTO);
        break;
      }
      case 'b': {
        keywordOrIdentifier("break", TokenType::BREAK);
        break;
      }
      case 'c': {
        
      }
      case 'd': {

      }
      case 'e': {
        if (!isAtEnd()) {
          if (peek() == 'l') {
            keywordOrIdentifier("else", TokenType::ELSE);
            break;
          } else if (peek() == 'n') {
            keywordOrIdentifier("enum", TokenType::ENUM);
            break;
          } else if (peek() == 'x') {
            keywordOrIdentifier("extern", TokenType::EXTERN);
            break;
          }
        }
      }
      case 'f': {
        if (!isAtEnd()) {
          if (peek() == 'o') {
            keywordOrIdentifier("for", TokenType::FOR);
            break;
          } else if (peek() == 'l') {
            keywordOrIdentifier("float", TokenType::FLOAT);
            break;
          }
        }
      }
      case 'g': {
        keywordOrIdentifier("goto", TokenType::GOTO);
        break;
      }
      case 'i': {
        if (!isAtEnd()) {
          if (peek() == 'n') {
            keywordOrIdentifier("int", TokenType::INT);
            break;
          } else if (peek() == 'f') {
            keywordOrIdentifier("if", TokenType::IF);
            break;
          }
        }
      }
      case 'l': {
        keywordOrIdentifier("long", TokenType::LONG);
        break;
      }
      case 'r': {
        
      }
      case 's': {
        
      }
      case 't': {
        keywordOrIdentifier("typedef", TokenType::TYPEDEF);
        break;
      }
      case 'u': {
        
      }
      case 'v': {
        
      }
      case 'w': {
        keywordOrIdentifier("while", TokenType::WHILE);
        break;
      }
      default: {
        std::cout << "Unknown token " << c << "." << std::endl;
      }
    }
  }

  debugTokens(_tokens);
}

void Lexer::preproc() {
  auto c = this->advance();
  if (!this->isAlpha(c)) {
    this->reportError("Expected alpha after #");
    return;
  }

  auto peek = this->peek();
  while(this->isAlpha(peek)) {
    this->advance();
    peek = this->peek();
  }

  if (!this->isWhitespace(peek)) {
    this->reportError("Expected whitespace after #");
    return;
  }

  this->addToken(TokenType::PREPROC_KEYWORD);
  this->advance();
}

void Lexer::preprocInclude() {
  while (peek() != '>' && !isAtEnd()) {
    auto c = advance();
  }

  if (isAtEnd()) {
    reportError("Expected > after < but got EOF.");
    return;
  }

  advance(); // consume last >
  this->addToken(TokenType::PREPROC_INCLUDE_VALUE);
}

void Lexer::keywordOrIdentifier(const std::string name, TokenType tokenType) {
  if (_start + name.size() < _source.size()) {
    const char *sourceStart = _source.c_str() + _start;
    const char *targetStart = name.c_str();
    std::cout << name << std::endl;

    if (memcmp(sourceStart, targetStart, name.size()) == 0) {
      _current += name.size() - 1;
      this->addToken(tokenType);
    }
  }

}

// Utils
void Lexer::skipWhitespaces() {
  while (!isAtEnd()) {
    auto c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t': {
        advance();
        continue;
      }
      case '\n': {
        _line++;
        advance();
        continue;
      }
      case '/': {
        if (peekNext() == '/') {
          while (peek() != '\n' && !isAtEnd()) {
            // once we hit the \n, the scanner will re-start skipWhitespaces on the next line
            advance();
          }
        }
      }
    }

    return;
  }
}

bool Lexer::isAlpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isWhitespace(const char c) {
  return c == ' ' || c == '\t';
}

char Lexer::advance() {
  _current++;
  return _source.at(_current - 1);
}

char Lexer::peek() {
  return _source.at(_current);
}

char Lexer::peekNext() {
  return _source.at(_current + 1);
}

char Lexer::peekAt(unsigned int index) {
  return _source.at(_current + index);
}

void Lexer::addToken(TokenType type) {
  // Extract the lexeme
  std::string lexeme = _source.substr(_start, _current - _start);

  // Add the token
  _tokens.push_back(Token(type, lexeme, _line, _start, _current));
}

bool Lexer::isAtEnd() {
  return _current >= _source.size();
}

void Lexer::reportError(std::string content) {
  std::cout << content << std::endl;
  std::cout << "at line " << _line << "." << std::endl;
}

void Lexer::debugTokenString() {
  std::cout << _source.substr(_start, _current - _start) << std::endl;
}