
typedef enum {
	SYMBOL,
	NUMBER,
	OPERATOR,
	RPAREN,
	LPAREN,
	RCB,
	LCB,
	END_OF_INPUT
} TokenType;

typedef struct {
	TokenType type;
	char* value;
} Token;

