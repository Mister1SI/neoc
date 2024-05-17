#include <lines.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return -1;
	struct stat st;
	fstat(fd, &st);
	long filesize = st.st_size;
	char* data = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (!data)
		return -2;
	close(fd);
	int lines_num = count_lines(data, filesize);
	void** arrs = get_lines(data, filesize, lines_num);
	char** lines = arrs[0];
	int* lines_len = arrs[1];
	for (int i=0;i<lines_num;i++) {
		printf("%d:	%s", lines_len[i], lines[i]);
	}
	munmap(data, filesize);
	return 0;
}

