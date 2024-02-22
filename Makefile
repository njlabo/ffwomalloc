CFLAGS=-Wall -g
SRCS=$(wildcard *.c)
EXES=$(SRCS:.c=.exe)

all: $(EXES)

%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXES)

.PHONY: clean
