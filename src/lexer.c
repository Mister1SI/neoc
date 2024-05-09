// This file contains the lexer that transforms code into meaningful symbols
// It currently does nothing
// TODO: make it do something
//

#include <lexer.h>
#include <stdio.h>
#include <token.h>

static _Bool is_numeric(char c) { return '0' <= c && c <= '9'; }

static _Bool is_alphabetic(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

static _Bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\v';
}

static size_t lex_number(Lexer l) {
    char c = l.expr[l.pos];
    size_t len = 0;
    while (is_numeric(c)) {
        if (l.pos + len >= l.len) {
            break;
        }
        len += 1;
        c = l.expr[l.pos + len];
    }
    return len;
}

static size_t lex_symbol(Lexer l) {
    char c = l.expr[l.pos];
    size_t len = 0;
    while (is_alphabetic(c)) {
        if (l.pos + len >= l.len) {
            break;
        }
        len += 1;
        c = l.expr[l.pos + len];
    }
    return len;
}

void eat_whitespace(Lexer *l) {
    char c = l->expr[l->pos];
    while (is_whitespace(c)) {
        if (l->pos + 1 >= l->len) {
            break;
        }
        l->pos += 1;
        c = l->expr[l->pos];
    }
}

Token lex_next_token(Lexer *l) {
    Token token = {
        .start = l->expr + l->pos,
    };
    if (l->pos >= l->len) {
        token.type = END_OF_FILE;
        return token;
    }

    eat_whitespace(l);

    printf("%zu\n", l->pos);

    token.start = l->expr + l->pos;
    char c = l->expr[l->pos];
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case '.':
        l->pos += 1;
        token.type = c;
        token.len = 1;
        return token;
    }

    if (is_numeric(c)) {
        token.type = NUMBER;
        token.len = lex_number(*l);
        l->pos += token.len;
        return token;
    }

    if (is_alphabetic(c)) {
        token.type = SYMBOL;
        token.len = lex_symbol(*l);
        l->pos += token.len;
        return token;
    }

    token.type = ILLEGAL;
    l->pos += 1;
    return token;
}

Lexer new_lexer(const char *expression, size_t length) {
    Lexer l = {0};
    l.expr = expression;
    l.len = length;
    return l;
}
