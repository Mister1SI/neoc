// This file contains the lexer that transforms code into meaningful symbols
// It currently does nothing
// TODO: make it do something
//


// Types of tokens understood
typedef enum {
	NUMBER,
	OPERATOR,
	END_OF_INPUT
} TokenType;

// Representation of a token
typedef struct {
	TokenType type;
	char* value;
} Token;



int lexer(char* filedata, long filelen) {
	
	return 1;
}


