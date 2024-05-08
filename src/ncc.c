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

int b(char* filename) {

	// Open the file
	int fd = open(filename, O_RDWR);
	if (fd == -1) {
		puts("Failed to open file.");
		return 0;
	}

	// Create the .pp preprocessed file's name
	int filename_len = strlen(filename);
	char* output_filename = malloc(filename_len);
	memcpy(output_filename, filename, filename_len);
	output_filename[filename_len-1] = 'p';
	output_filename[filename_len-2] = 'p';

	// Get file length
	struct stat st;
	fstat(fd, &st);
	long filelen = st.st_size;
	
	// Call mmap
	char* filedata = mmap(0, filelen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (filedata == (void*)-1) {
		puts("Failed to map memory.");
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

