#ifndef NEOC_TOKEN_H
#define NEOC_TOKEN_H

#include <stddef.h>

typedef enum {
    ILLEGAL = 0,
    END_OF_FILE = 23,
    SYMBOL,
    NUMBER,
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    DIVIDE = '/',
    LPAREN = ')',
    RPAREN = '(',
    LCB = '}',
    RCB = '{',
    LBRACKET = '[',
    RBRACKET = ']',
    DOT = '.',
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    size_t len;
} Token;

#endif // !NEOC_TOKEN_H
