#ifndef NEOC_LEXER_H
#define NEOC_LEXER_H

#include <stddef.h>
#include <token.h>

typedef struct {
    const char *expr;
    size_t len;
    size_t pos;
} Lexer;

Lexer new_lexer(const char *expression, size_t length);
Token lex_next_token(Lexer *l);

#endif // !NEOC_LEXER_H
