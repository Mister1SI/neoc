// This file contains the entry point and help function
// It reads the arguments and invokes the compiler for each one
// TODO: invoke linkerwith resultant object files
//

#include <stdio.h>

extern int ncc(char *);

void help();

#include <lexer.h>
#include <token.h>

void print_tok(Token t) {
    switch (t.type) {
    case SYMBOL:
    case NUMBER:
        printf("<%.*s> %zu\n", (int)t.len, t.start, t.len);
        return;
    case ILLEGAL:
        puts("ILLEGAL");
        return;
    case END_OF_FILE:
        puts("EOF");
        return;
    default:
        printf("<%c>\n", *t.start);
        return;
    }
}

int main(int argc, char **argv) {

    // if (argc == 1) {
    // 	help();
    // 	return 0;
    // }
    //
    // for (int i=1; i<argc; i++) {
    // 	if(!ncc(argv[i])) {
    // 		puts("Compilation failed.");
    // 		return -1;
    // 	}
    // }

    const char expr[] = "apple + bananana- cheese";
    Lexer l = new_lexer(expr, sizeof expr - 1);
    Token t = {0};
    while (t.type != END_OF_FILE) {
        t = lex_next_token(&l);
        print_tok(t);
    }

    return 0;
}

void help() { puts("I\'m helping"); }
