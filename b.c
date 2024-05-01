extern int preprocessor(char*);

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int b(char* filename) {

	// Open the file
	int fd = open(filename, O_RDWR);
	if (fd == -1) {
		puts("Failed to open file.");
		return 0;
	}

	// Get file length
	struct stat st;
	fstat(&st);
	long filelen = st.st_size;
	
	// Call mmap
	char* filedata = mmap(0, filelen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (filedata = (void*)-1) {
		puts("Failed to map memory.");
		return 0;
	}
	close(fd);
	
	// Invoke the preprocessor
	if(!preprocessor(filedata)) {
		puts("Preprocessor error. Terminating.");
		return 0;
	}

	// Unmap & return
	munmap(filedata, filelen);
	return 1;
}

