#ifndef LETT_LT_LEXER_H
#define LETT_LT_LEXER_H

#include <stdlib.h>

struct lt_lexer {
    const char *start;
    const char *current;
    size_t line;
};

enum lt_token_type {
    LT_TOKEN_EOF, LT_TOKEN_ERR,

    LT_TOKEN_L_PAREN, LT_TOKEN_R_PAREN, // ( )
    LT_TOKEN_L_BRACE, LT_TOKEN_R_BRACE, // { }
    LT_TOKEN_L_BRACKET, LT_TOKEN_R_BRACKET, // [ ]

    LT_TOKEN_DOT, LT_TOKEN_COMMA, LT_TOKEN_COLON, // . , :

    LT_TOKEN_PLUS, LT_TOKEN_MINUS, // + -
    LT_TOKEN_STAR, LT_TOKEN_SLASH, // * /
    LT_TOKEN_GREATER, LT_TOKEN_GREATER_EQUAL, // > >=
    LT_TOKEN_LESS, LT_TOKEN_LESS_EQUAL, // < <=
    LT_TOKEN_OR, LT_TOKEN_AND, // || &&
    LT_TOKEN_L_PIPE, LT_TOKEN_R_PIPE, // <| |>

    LT_TOKEN_KEY_STRUCT, LT_TOKEN_KEY_SELF, // struct, self
    LT_TOKEN_KEY_LET, LT_TOKEN_KEY_PRINT, // let, print
    LT_TOKEN_KEY_FN, LT_TOKEN_KEY_RETURN, // fn, return
    LT_TOKEN_KEY_IF, LT_TOKEN_KEY_ELSE, // if, else
    LT_TOKEN_KEY_WHILE, LT_TOKEN_KEY_FOR, // while, for
    LT_TOKEN_KEY_TRUE, LT_TOKEN_KEY_FALSE, // true, false
    LT_TOKEN_KEY_MATCH, LT_TOKEN_KEY_WITH, // match, with

    LT_TOKEN_IDENTIFIER, LT_TOKEN_STRING, LT_TOKEN_NUMBER,
};

struct lt_token {
    enum lt_token_type type;
    const char *start;
    size_t length;
    size_t line;
};

void lt_lexer_init(struct lt_lexer *lexer, const char *source);
struct lt_token lt_lexer_next(struct lt_lexer *lexer);

#endif //LETT_LT_LEXER_H
