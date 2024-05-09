// preprocessor.c
// This file contains the preprocessor
// It currently REMOVES COMMENTS
// TODO: FILE INCLUSION, MACRO EXPANSION
// 

static void reset();

static int com_sl;
static int com_ml;
static int rep_char = 0;	// The character to replace comments with



#include <stdio.h>
#include <ANSI-colors.h>
#include <unistd.h>
#include <error.h>

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



	com_sl = 0;
	com_ml = 0;

	char* cb = filedata;		// Current byte

	// Check each byte
	for (long i=0; i<filelen; i++) {			
		
		int _i = i;
		_i++;
		// Check if file ends in '/'
		if (*cb == '/' && _i == filelen) {
			// File ends in '/', jump to next iteration
			continue;
		}

		if (!com_ml && com_sl && *cb == '\n')
			reset();

		// Single-line comments
		if(!com_sl) {
			if (*cb == '/' && *(cb+1) == '/') {
					com_sl = 1;
					// No call to fputc() because this char is a comment
			}
		} else {
			// No call to fputc() because this char is a comment
		}
		// Multi-line comments
		if(!com_ml) {
			if (*cb == '/' && *(cb+1) == '*') {
				com_ml = 1;
				// No call to fputc() because this char is a comment
			}
		} else {
			// First check for the end of the multiline comment
			if (*cb == '*' && *(cb+1) == '/') {
				com_ml = 0;
				// No call to fputc() because this char and the next are comments
			} else {
				// No call to fputc() because this char is a comment
			}
		}

		fputc(*cb, file);
		// Increment the byte pointer
		cb++;
	}

	fclose(file);
	return 1;
}

void reset() {
	
	com_sl = 0;

}


