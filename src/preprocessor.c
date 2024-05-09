// preprocessor.c
// This file contains the preprocessor
// It currently REMOVES COMMENTS
// TODO: FILE INCLUSION, MACRO EXPANSION
// 

static void reset();

static int com_sl;
static int com_ml;

#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>

int preprocessor(char* filedata, long filelen, char* output_filename) {

	if (access(output_filename, F_OK) == 0) {
		ncc_error("Preprocessor: ", "Output file already exists.");
		return 0;
	}
	FILE* file = fopen(output_filename, "w");
	if (!file) {
		ncc_error("Preprocessor: ", "Failed to open file.");
		return 0;
	}

	

	fclose(file);
	return 1;
}

char* read_line(char* line, int len, int* out_len) {

}

void reset() {
	
	com_sl = 0;

}


