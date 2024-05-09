// This file contains the compiler function that is invoked for every file
// It invokes the preprocessor
// TODO: implement LEXING, PARSING, SEMANTIC ANALYSIS, OPTIMIZATION, GENERATION
//


extern int preprocessor(char*, long, char*);

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <error.h>

int ncc(char* filename) {

	// Open the file
	int fd = open(filename, O_RDWR);
	if (fd == -1) {
		ncc_error("ncc: ", "Failed to open file.");
		return 0;
	}

	// Create the .pof (preprocessor output file) preprocessed file's name
	int filename_len = strlen(filename);
	int ofilename_len = filename_len;
	int last_period_index;
	// Recursively check to find a file extension
	for (int i=filename_len-1;i>-1;i--) {
		last_period_index = -1;
		char cb = filename[i];
		if (cb == '.') {
			last_period_index = i;
			break;
		}
	}
	int ext_len = filename_len - last_period_index;
	int extra_bytes = 0;
	if (ext_len < 3)
		extra_bytes = 3 - ext_len;
	char* output_filename = malloc(filename_len+extra_bytes);
	memcpy(output_filename, filename, filename_len);
	memcpy(output_filename+last_period_index+1, "pof", 3);

	// Get file length
	struct stat st;
	fstat(fd, &st);
	long filelen = st.st_size;
	
	// Call mmap
	char* filedata = mmap(0, filelen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (filedata == (void*)-1) {
		ncc_error("ncc: ", "Failed to map memory.");
		switch (errno) {
			case EACCES:
				puts("EACCES");
				break;
			case EBADF:
				puts("Bad FD");
				break;
			case EINVAL:
				puts("EINVAL");
				break;
			default:
				puts("Other error");
				break;
		}
		return 0;
	}
	close(fd);
	
	// Invoke the preprocessor
	if(!preprocessor(filedata, filelen, output_filename)) {
		puts("Preprocessor error. Terminating.");
		return 0;
	}

	// Unmap & return
	munmap(filedata, filelen);
	return 1;
}

