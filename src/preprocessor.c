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
	int olen = 0;
	char* obuf = malloc(len);
	for (int i=0;i<len;i++) {
		char cb = line[i];
		if (!com_sl && !com_ml) {
			if (cb == '/') {
				if (line[i+1] == '/') {
					com_sl = 1;
					continue;
				}
				if (line[i+1] == '*') {
					com_ml = 1;
					continue;
				}
				olen++;
			} else {
				olen++;
			}
		}
		else if (com_sl) {
			if (cb == '\n') {
				com_sl = 0;
				obuf[olen] = 'n'
			}	// else don't do anything because of the single line comment
		} else if (com_ml) {
			if (cb == '*' && line[i+1] == '/') {
				com_ml = 0;
				i++;
			}
		} else {
			// Some weird condition arose
			ncc_error("Preprocessor: ", "Invalid state: inside both single- and multi-line comments.");
		}
	}
	*out_len = olen;
	return obuf;
}

void reset() {
	
	com_sl = 0;

}


