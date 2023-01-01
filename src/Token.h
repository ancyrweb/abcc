#ifndef ABCC_TOKEN_H
#define ABCC_TOKEN_H

#include <string>

enum class TokenType {
    PLUS, MINUS, STAR, SLASH, MODULO, // + - * / %
    EQUAL_EQUAL, BANG_EQUAL, // == !=
    GREATER, GREATER_EQUAL, LOWER, LOWER_EQUAL, // > >= < <=
    LOGICAL_AND, LOGICAL_OR, // && ||
    BANG, // !
    INCREMENT, DECREMENT, // ++ --
    BITWISE_AND, BITWISE_XOR, BITWISE_OR, // & ^ |
    BITWISE_SHIFT_LEFT, BITWISE_SHIFT_RIGHT, // << >>

    // = += -= *= /= %= <<= >>=
    ASSIGN, ASSIGN_PLUS_EQUAL, ASSIGN_MINUS_EQUAL, ASSIGN_STAR_EQUAL, ASSIGN_SLASH_EQUAL,
    ASSIGN_MODULO_EQUAL, ASSIGN_BITWISE_SHIFT_LEFT, ASSIGN_BITWISE_SHIFT_RIGHT,

    LEFT_PAREN, RIGHT_PAREN, // ( )
    LEFT_BRACE, RIGHT_BRACE, // { }
    LEFT_BRACKET, RIGHT_BRACKET, // [ ]
    COMMA, // ,
    DOT, // .
    SEMICOLON, // ;
    BACK_SLASH, // \ (for multiline)
    ARROW, // ->
    UNDERSCORE, // _

    STRING, INTEGER, DECIMAL,
    IDENTIFIER,

    // Preproc
    PREPROC_KEYWORD, // #include #define ...
    PREPROC_INCLUDE_VALUE,

    // Keywords (https://www.ibm.com/docs/en/developer-for-zos/14.2?topic=programs-c-reserved-keywords)
    AUTO,
    BREAK,
    CASE,
    CHAR,
    CONST,
    CONTINUE,
    DEFAULT,
    DO,
    DOUBLE,
    ELSE,
    ENUM,
    EXTERN,
    FLOAT,
    FOR,
    GOTO,
    IF,
    INT,
    LONG,
    REGISTER,
    RETURN,
    SHORT,
    SIGNED,
    SIZEOF,
    STATIC,
    STRUCT,
    SWITCH,
    TYPEDEF,
    UNION,
    UNSIGNED,
    VOID,
    VOLATILE,
    WHILE,

    END_OF_FILE,
};

class Token {
public:
    Token(TokenType, std::string lexeme, int line, int start, int end);
    TokenType getType();
    std::string getLexeme();
    int getLine();
    int getStart();
    int getEnd();

private:
    TokenType _type;
    std::string _lexeme;
    int _line;
    int _start;
    int _end;
};

#endif //ABCC_TOKEN_H
