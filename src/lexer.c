// This file contains the lexer that transforms code into meaningful symbols
// It currently does nothing
// TODO: make it do something
//

#include <stdlib.h>
#include <lexer.h>

Token* next_token(char* input, int* pos) {
	char cb = input[*pos];

	Token* token = malloc(sizeof(Token));
	token->value = malloc(2);
	token->value[1] = 0;
	switch(cb) {
		case '+':
		case '-':
		case '*':
		case '/':
			token->type = OPERATOR;
			token->value[0] = cb;
			break;
		case '(':
			token->type = LPAREN;
			token->value[0] = cb;
			break;
		case ')':
			token->type = RPAREN;
			token->value[0] = cb;
			break;
		case '{':
			token->type = LCB;
			token->value[0] = cb;
			break;
		case '}':
			token->type = RCB;
			token->value[0] = cb;
			break;
		default:
			free(token);
			return 0;
	}

	(*pos)++;
	return token;
}

int lexer(char* filedata, long filelen) {
	
	return 1;
}


