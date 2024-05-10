#ifndef LINES_H
#define LINES_H

#include <stdio.h>

int count_lines(char* in_data, long len) {
	char* data = in_data;
	int lines = 0;

	for (long i=0;i<len;i++) {
		if (*data == '\n')
			lines++;
	}
	return lines;
}

#endif // !LINES_H
