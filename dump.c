#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	char *data;
	int i, fd = open(argv[1], O_RDONLY);
	off_t bytes = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	data = mmap(NULL, bytes, PROT_READ, MAP_PRIVATE, fd, 0);
	for (i = 0; i < bytes; i++)
		printf("%02x ", data[i]);
	printf("\n");
	return 0;
}
