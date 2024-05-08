#include <ANSI-colors.h>
#include <stdio.h>

void error(char* src, char* msg) {
	fputs(src, stdout);
	fputs(ANSI_BRED, stdout);
	fputs("Error: ", stdout);
	fputs(ANSI_RESET, stdout);
	fputs(msg, stdout);
	fputc('\n', stdout);
	fflush(stdout);
}

