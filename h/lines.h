#ifndef LINES_H
#define LINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char* in_data, long len) {
	char* data = in_data;
	int lines = 0;

	for (long i=0;i<len;i++) {
		if (*data == '\n')
			lines++;
	}
	return lines;
}

// Returns void*[2]
// [0] is the char** array pointer
// [1] is the length per line
void** get_lines(char* data, long len, int lines) {
	char** lines_arr = malloc(lines * sizeof(char*));
	int* len_arr = malloc(lines * sizeof(int));
	if (!lines_arr || !len_arr)
		return NULL;
	char* start = data;
	long line_len = 0;
	long line_index = 0;
	// Iterate over every character to distinguish the individual lines.
	// Newlines are not included in the arrays
	for (long i=0;i<lines;i++) {
		if (data[i] == '\n') {
			lines_arr[line_index] = malloc(line_len);
			if (!lines_arr[line_index]) {
				perror("Memory alloc failed in get_lines function");
				break;
			}
			strncpy(lines_arr[line_index], start, line_len-1);
			line_len = 0;
			line_index++;
		} else {
			line_len++;
		}
	}
	void** return_arr = malloc(2*sizeof(void*));
	return_arr[0] = lines_arr;
	return_arr[1] = len_arr;
	return return_arr;
}

#endif // !LINES_H
