#ifndef ABCC_DEBUG_H
#define ABCC_DEBUG_H

#include <string>
#include <iostream>
#include <vector>
#include "Token.h"

std::string tokenToString(TokenType t) {
  switch (t) {
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::STAR: return "STAR";
    case TokenType::SLASH: return "SLASH";
    case TokenType::MODULO: return "MODULO";
    case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
    case TokenType::BANG_EQUAL: return "BANG_EQUAL";
    case TokenType::GREATER: return "GREATER";
    case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
    case TokenType::LOWER: return "LOWER";
    case TokenType::LOWER_EQUAL: return "LOWER_EQUAL";
    case TokenType::LOGICAL_AND: return "LOGICAL_AND";
    case TokenType::LOGICAL_OR: return "LOGICAL_OR";
    case TokenType::BANG: return "BANG";
    case TokenType::INCREMENT: return "INCREMENT";
    case TokenType::DECREMENT: return "DECREMENT";
    case TokenType::BITWISE_AND: return "BITWISE_AND";
    case TokenType::BITWISE_XOR: return "BITWISE_XOR";
    case TokenType::BITWISE_OR: return "BITWISE_OR";
    case TokenType::BITWISE_SHIFT_LEFT: return "BITWISE_SHIFT_LEFT";
    case TokenType::BITWISE_SHIFT_RIGHT: return "BITWISE_SHIFT_RIGHT";
    case TokenType::ASSIGN: return "ASSIGN";
    case TokenType::ASSIGN_PLUS_EQUAL: return "ASSIGN_PLUS_EQUAL";
    case TokenType::ASSIGN_MINUS_EQUAL: return "ASSIGN_MINUS_EQUAL";
    case TokenType::ASSIGN_STAR_EQUAL: return "ASSIGN_STAR_EQUAL";
    case TokenType::ASSIGN_SLASH_EQUAL: return "ASSIGN_SLASH_EQUAL";
    case TokenType::ASSIGN_MODULO_EQUAL: return "ASSIGN_MODULO_EQUAL";
    case TokenType::ASSIGN_BITWISE_SHIFT_LEFT: return "ASSIGN_BITWISE_SHIFT_LEFT";
    case TokenType::ASSIGN_BITWISE_SHIFT_RIGHT: return "ASSIGN_BITWISE_SHIFT_RIGHT";
    case TokenType::LEFT_PAREN: return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
    case TokenType::LEFT_BRACE: return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
    case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
    case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
    case TokenType::COMMA: return "COMMA";
    case TokenType::DOT: return "DOT";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::BACK_SLASH: return "BACK_SLASH";
    case TokenType::ARROW: return "ARROW";
    case TokenType::UNDERSCORE: return "UNDERSCORE";
    case TokenType::STRING: return "STRING";
    case TokenType::INTEGER: return "INTEGER";
    case TokenType::DECIMAL: return "DECIMAL";
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::PREPROC_KEYWORD: return "PREPROC_KEYWORD";
    case TokenType::PREPROC_INCLUDE_VALUE: return "PREPROC_INCLUDE_VALUE";

    case TokenType::AUTO: return "AUTO";
    case TokenType::BREAK: return "BREAK";
    case TokenType::CASE: return "CASE";
    case TokenType::CHAR: return "CHAR";
    case TokenType::CONST: return "CONST";
    case TokenType::CONTINUE: return "CONTINUE";
    case TokenType::DEFAULT: return "DEFAULT";
    case TokenType::DO: return "DO";
    case TokenType::DOUBLE: return "DOUBLE";
    case TokenType::ELSE: return "ELSE";
    case TokenType::ENUM: return "ENUM";
    case TokenType::EXTERN: return "EXTERN";
    case TokenType::FLOAT: return "FLOAT";
    case TokenType::FOR: return "FOR";
    case TokenType::GOTO: return "GOTO";    
    case TokenType::IF: return "IF";
    case TokenType::INT: return "INT";
    case TokenType::LONG: return "LONG";
    case TokenType::REGISTER: return "REGISTER";
    case TokenType::RETURN: return "RETURN";    
    case TokenType::SHORT: return "SHORT";
    case TokenType::SIGNED: return "SIGNED";
    case TokenType::SIZEOF: return "SIZEOF";
    case TokenType::STATIC: return "STATIC";
    case TokenType::STRUCT: return "STRUCT";    
    case TokenType::SWITCH: return "SWITCH";
    case TokenType::TYPEDEF: return "TYPEDEF";
    case TokenType::UNION: return "UNION";
    case TokenType::UNSIGNED: return "UNSIGNED";
    case TokenType::VOID: return "VOID";    
    case TokenType::VOLATILE: return "VOLATILE";
    case TokenType::WHILE: return "WHILE";
    case TokenType::END_OF_FILE: return "END_OF_FILE";

    default: return "UNKNOWN";
  }
}

void debugTokens(std::vector<Token> tokens) {
  for (auto token: tokens) {
    std::cout << tokenToString(token.getType()) << " | ";
    std::cout << token.getStart() << " - " << token.getEnd() << " | ";
    std::cout << token.getLexeme();
    std::cout << std::endl;
  }
}

#endif