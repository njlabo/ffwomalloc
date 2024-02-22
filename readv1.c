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
	char weight[0];
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main()
{
	const char *fname = "v1.bin";
	int i, fd, total = 0;
	off_t bytes;
	struct layer *l;

	fd = open(fname, O_RDONLY);
	bytes = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	l = mmap(NULL, bytes, PROT_READ, MAP_PRIVATE, fd, 0);
	for (i = 0; total < bytes; i++) {
		int j;
		size_t sz = l->nrows * l->ncols;
		total += sz + 2;
		printf("layer[%d] (%d, %d) ", i, l->nrows, l->ncols);
		for (j = 0; j < sz; j++)
			printf("%02x ", l->weight[j]);
		printf("\n");
		l = (struct layer *)((char *)l + sz + 2); // moving pointer is complicated!
	}
	return 0;
}
