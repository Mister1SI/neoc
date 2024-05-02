// preprocessor.c
// This file contains the preprocessor
// It currently REMOVES COMMENTS
// TODO: FILE INCLUSION, MACRO EXPANSION
// 

static void reset();

static int com_sl;
static int com_ml;
static int rep_char = 0;	// The character to replace comments with

int preprocessor(char* filedata, long filelen) {

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
					*cb = rep_char;
			}
		} else {
			*cb = rep_char;
		}

		// Multi-line comments
		if(!com_ml) {
			if (*cb == '/' && *(cb+1) == '*') {
				com_ml = 1;
				*cb = rep_char;
			}
		} else {
			// First check for the end of the multiline comment
			if (*cb == '*' && *(cb+1) == '/') {
				com_ml = 0;
				*cb = rep_char;
				*(cb+1) = rep_char;
			} else {
				*cb = rep_char;
			}
		}

		// Increment the byte pointer
		cb++;
	}

	return 1;
}

void reset() {
	
	com_sl = 0;

}


