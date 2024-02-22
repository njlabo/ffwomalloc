#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct layer {
	char nrows;
	char ncols;
	char weight[0];
};

struct layer layers[] = {
	{
		.nrows = 2,
		.ncols = 3,
	},
	{
		.nrows = 3,
		.ncols = 1,
	},
	{
		.nrows = 1,
		.ncols = 2,
	},
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main()
{
	int i, fd = open("v1.bin", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	for (i = 0; i < ARRAY_SIZE(layers); i++) {
		int j;
		struct layer *l = &layers[i];
		write(fd, l, sizeof(*l));
		for (j = 0; j < l->nrows * l->ncols; j++) {
			char val = '0' + j;
			write(fd, &val, 1);
		}
	}
	close(fd);
	return 0;
}


