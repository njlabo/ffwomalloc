#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

struct layer {
	char nrows;
	char ncols;
	char offset;
};

int main()
{
	const char *fname = "v2.bin";
	int i, fd;
	off_t bytes;
	struct layer *l;
	char *num_layers;

	fd = open(fname, O_RDONLY);
	bytes = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	num_layers = mmap(NULL, bytes, PROT_READ, MAP_PRIVATE, fd, 0);
	l = (struct layer *)(num_layers + 1);
	for (i = 0; i < *num_layers; i++) {
		int j;
		size_t sz = l[i].nrows * l[i].ncols;
		char *data = (char *)l + l[i].offset;

		printf("layer[%d] (%d, %d) %d ", i, l[i].nrows, l[i].ncols, l[i].offset);
		for (j = 0; j < sz; j++)
			printf("%02x ", data[j]);
		printf("\n");
	}
	return 0;
}
