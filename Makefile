CC = gcc
CFLAGS = -Wno-implicit-function-declaration -Wno-incompatible-pointer-types

SRCS = 1.c 2.c 3.c 4.c 5.c 6-client.c 6-server.c 7.c 8.c intro.c pipe.c
OBJS = $(SRCS:.c=.o)
PROGS = $(SRCS:.c=.out)

all: $(PROGS)

%.out: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(PROGS)