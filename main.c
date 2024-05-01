#include <stdio.h>

extern int b(char*);

void help();

int main(int argc, char** argv) {

	if (argc == 1) {
		help();
		return 0;
	}
	
	for (int i=1; i<argc; i++) {
		if(!b(argv[i])) {
			puts("Compilation failed.");
			return -1;
		}
	}

	return 0;
}

void help() {
	puts("I\'m helping");
}

