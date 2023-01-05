#include "Lexer.h"
#include "Debug.h"

#include <iostream>

Lexer::Lexer(): _line(0), _start(0), _current(0), _tokens() {

}

void Lexer::scan(const std::string source) {
  _source = source;

  while(!isAtEnd()) {
    skipWhitespaces();
    if (isAtEnd()) {
      // skipping whitespaces might lead us to the end of the file
      break;
    }

    _start = _current;

    auto c = advance();
    switch (c) {
      // Single-character tokens
      case ';': { addToken(TokenType::SEMICOLON); break; }
      case '{': { addToken(TokenType::LEFT_BRACE); break; }
      case '}': { addToken(TokenType::RIGHT_BRACE); break; }
      case '(': { addToken(TokenType::LEFT_PAREN); break; }
      case ')': { addToken(TokenType::RIGHT_PAREN); break; }
      case '[': { addToken(TokenType::LEFT_BRACKET); break; }
      case ']': { addToken(TokenType::RIGHT_BRACKET); break; }
      case ',': { addToken(TokenType::COMMA); break; }
      case '.': { addToken(TokenType::DOT); break; }
      case '^': { addToken(TokenType::BITWISE_XOR); break; }
      case '\\': { addToken(TokenType::BACK_SLASH); break; }
      // Handling characters starting by + - * / -
      case '+': {
        if (peek() == '+') {
          advance();
          addToken(TokenType::INCREMENT);
          break;
        } else if (peek() == '=') {
          advance();
          addToken(TokenType::ASSIGN_PLUS_EQUAL);
          break;
        } 

        addToken(TokenType::PLUS);
        break;
      }
      case '-': {
        if (peek() == '-') {
          advance();
          addToken(TokenType::DECREMENT);
          break;
        } else if (peek() == '=') {
          advance();
          addToken(TokenType::ASSIGN_MINUS_EQUAL);
          break;
        } 

        addToken(TokenType::MINUS);
        break;
      }
      case '*': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::ASSIGN_STAR_EQUAL);
          break;
        } 

        addToken(TokenType::STAR);
        break;
      }
      case '/': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::ASSIGN_SLASH_EQUAL);
          break;
        } 

        addToken(TokenType::SLASH);
        break;
      }
      case '%': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::ASSIGN_MODULO_EQUAL);
          break;
        } 

        addToken(TokenType::ASSIGN);
        break;
      }
      // Handling = ! == !=
      case '=': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::EQUAL_EQUAL);
          break;
        } 

        addToken(TokenType::ASSIGN);
        break;
      }
      case '!': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::BANG_EQUAL);
          break;
        } 

        addToken(TokenType::BANG);
        break;
      }
      // Handling & &&
      case '&': {
        if (peek() == '&') {
          advance();
          addToken(TokenType::LOGICAL_AND);
          break;
        } 

        addToken(TokenType::BITWISE_AND);
        break;
      }
      // Handling | ||
      case '|': {
        if (peek() == '|') {
          advance();
          addToken(TokenType::LOGICAL_OR);
          break;
        } 

        addToken(TokenType::BITWISE_OR);
        break;
      }
      // Preprocessor directives
      case '#': {
        preproc();
        break;
      }
      // Handling Comparison + Bitwise < <= << <<=
      case '<': {
        if (isAlpha(peek())) {
          preprocInclude();
          break;
        } 

        if (peek() == '=') {
          advance();
          addToken(TokenType::LOWER_EQUAL);
          break;
        } 
        
        if (peek() == '<') {
          advance();
          if (peekNext() == '=') {
            advance();
            addToken(TokenType::ASSIGN_BITWISE_SHIFT_LEFT);
            break;
          } 

          addToken(TokenType::BITWISE_SHIFT_LEFT);
          break;
        }
      
        addToken(TokenType::LOWER);
        break;
      }      
      // Handling Comparison + Bitwise > >= >> >>=
      case '>': {
        if (peek() == '=') {
          advance();
          addToken(TokenType::GREATER_EQUAL);
          break;
        } 
        
        if (peek() == '>') {
          advance();
          if (peekNext() == '=') {
            advance();
            addToken(TokenType::ASSIGN_BITWISE_SHIFT_RIGHT);
            break;
          } 

          addToken(TokenType::BITWISE_SHIFT_RIGHT);
          break;
        }
      
        addToken(TokenType::GREATER);
        break;
      }
      // Keywords & Identifiers
      case 'a': {
        keywordOrIdentifier("auto", TokenType::AUTO);
        break;
      }
      case 'b': {
        keywordOrIdentifier("break", TokenType::BREAK);
        break;
      }
      case 'c': {
         if (!isAtEnd()) {
          if (peek() == 'h') {
            keywordOrIdentifier("char", TokenType::CHAR);
            break;
          } else if (peek() == 'o' && peekAt(1) == 'n') {
            if (peekAt(2) == 's') {
              keywordOrIdentifier("const", TokenType::CONST);
              break;
            } else if (peekAt(2) == 't') {
              keywordOrIdentifier("continue", TokenType::CONTINUE);
              break;
            }
          } 
        }
      }
      case 'd': {
        if (!isAtEnd()) {
          if (peek() == 'e') {
            keywordOrIdentifier("default", TokenType::DEFAULT);
            break;
          } else if (peek() == 'o') {
            if (peekAt(1) == 'u') {
              keywordOrIdentifier("double", TokenType::DOUBLE);
              break;
            } 

            keywordOrIdentifier("do", TokenType::CONTINUE);
            break;
          } 
        }
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
        if (!isAtEnd()) {
          if (peek() == 'e') {
            if (peekAt(1) == 'g') {
              keywordOrIdentifier("register", TokenType::REGISTER);
              break;
            } else if (peekAt(1) == 't') {
              keywordOrIdentifier("return", TokenType::RETURN);
              break;
            }
          }   
        }
      }
      case 's': {
        if (!isAtEnd()) {
          if (peek() == 'i') {
            if (peekAt(1) == 'g') {
              keywordOrIdentifier("signed", TokenType::SIGNED);
              break;
            } else if (peekAt(1) == 'z') {
              keywordOrIdentifier("sizeof", TokenType::SIZEOF);
              break;
            }
          } else if (peek() == 't') {
            if (peekAt(1) == 'a') {
              keywordOrIdentifier("static", TokenType::STATIC);
              break;
            } else if (peekAt(1) == 'r') {
              keywordOrIdentifier("struct", TokenType::STRUCT);
              break;
            }
          } else if (peek() == 'w') {
            keywordOrIdentifier("switch", TokenType::SWITCH);
            break;
          } else if (peek() == 'h') {
            keywordOrIdentifier("short", TokenType::SHORT);
            break;
          }
        }
      }
      case 't': {
        keywordOrIdentifier("typedef", TokenType::TYPEDEF);
        break;
      }
      case 'u': {
        if (!isAtEnd()) {
          if (peek() == 'n') {
            if (peekAt(1) == 'i') {
              keywordOrIdentifier("union", TokenType::UNION);
              break;
            } else if (peekAt(1) == 's') {
              keywordOrIdentifier("unsigned", TokenType::UNSIGNED);
              break;
            }
          }
        }
      }
      case 'v': {
        if (!isAtEnd()) {
          if (peek() == 'o') {
            if (peekAt(1) == 'i') {
              keywordOrIdentifier("void", TokenType::VOID);
              break;
            } else if (peekAt(1) == 'l') {
              keywordOrIdentifier("volatile", TokenType::VOLATILE);
              break;
            }
          }
        }
      }
      case 'w': {
        keywordOrIdentifier("while", TokenType::WHILE);
        break;
      }
      // String literals
      case '"': {
        stringLiteral();
        break;
      }
      default: {
        if (isDigit(c)) {
          // Number literals (integers & decimals)
          numberLiteral();
          break;
        } else if (isAlpha(c)) {
          // Identifiers
          identifier();
          break;
        }

        std::cout << "Unknown token code " << (int)c << " " << c << "." << std::endl;
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

    if (memcmp(sourceStart, targetStart, name.size()) == 0) {
      if (isAlpha(peekAt(name.size() - 1))) {
        // It starts like a keyword but it continues with an alpha
        // something like returnV or shortTest should not be recognized
        // as two different tokens but as a single identifier, so we skip.
        return identifier();
      }

      _current += name.size() - 1;
      this->addToken(tokenType);
      return;
    }
  }

  return identifier();
}

void Lexer::stringLiteral() {
  while(peek() != '"' && !isAtEnd()) {
    advance();
  }

  if (isAtEnd()) {
    reportError("Expected closing \" but reached end of file.");
    return;
  }

  advance(); // consume closing "
  this->addToken(TokenType::STRING);
}

void Lexer::numberLiteral() {
  while(!isAtEnd() && isDigit(peek())) {
    advance();
  }

  if (peek() == '.') {
    while(!isAtEnd() && isDigit(peek())) {
      advance();
    }

    this->addToken(TokenType::DECIMAL);
    return;
  }

  this->addToken(TokenType::INTEGER);
}

void Lexer::identifier() {
  while (!isAtEnd() && (isAlpha(peek()) || peek() == '_')) {
    advance();
  }

  if (isAtEnd()) {
    reportError("Expected ; at end of file.");
    return;
  }

  this->addToken(TokenType::IDENTIFIER);
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
          continue;
        } else if (peekNext() == '*') {
          // TODO recognize multi-line comments
        }
      }
    }

    return;
  }
}

bool Lexer::isAlpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isDigit(const char c) {
  return c >= '0' && c <= '9';
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
  unsigned int at = _current + index;
  if (at > _source.size()) {
    return 0; // return null or any invalid character ?
  }

  return _source.at(_current + index);
}

void Lexer::addToken(TokenType type) {
  // Extract the lexeme
  std::string lexeme = _source.substr(_start, _current - _start);

  // Add the token
  _tokens.push_back(Token(type, lexeme, _line, _start, _current));
}

bool Lexer::isAtEnd() {
  return _current >= _source.size() - 1;
}

void Lexer::reportError(std::string content) {
  std::cout << content << std::endl;
  std::cout << "at line " << _line << "." << std::endl;
}

void Lexer::debugTokenString() {
  std::cout << _source.substr(_start, _current - _start) << std::endl;
}