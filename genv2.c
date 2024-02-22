#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

struct layer {
	char nrows;
	char ncols;
	char offset;
};
static struct layer layers[] = {
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

struct weight {
	int bytes;
	char *data;
};
static struct weight weight[ARRAY_SIZE(layers)];
	

int main()
{
	const char num_layers = ARRAY_SIZE(layers);
	int i, fd = open("v2.bin", O_WRONLY|O_CREAT|O_TRUNC, 0666);

	write(fd, &num_layers, 1);
	for (i = 0; i < ARRAY_SIZE(layers); i++) {
		int j;
		struct layer *l = &layers[i];

		weight[i].bytes = l->nrows * l->ncols;
		weight[i].data = malloc(weight[i].bytes);
		for (j = 0; j < l->nrows * l->ncols; j++)
			weight[i].data[j] = '0' + j;
	}
	for (i = 0; i < ARRAY_SIZE(layers); i++) {
		struct layer *l = &layers[i];

		if (i == 0)
			l->offset = ARRAY_SIZE(layers) * sizeof(*l);
		else
			l->offset = layers[i-1].offset + weight[i-1].bytes;
		write(fd, l, sizeof(*l));
	}
	for (i = 0; i < ARRAY_SIZE(layers); i++)
		write(fd, weight[i].data, weight[i].bytes);
	close(fd);
	return 0;
}


