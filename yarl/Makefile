CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0
LIBS=-lraylib -lm
DEPS=yarl.h backend.h

all: libyarl.so

%.so: yarl.o backend.o
	$(CC) $(CFLAGS) $(LIBS) $^ -shared -o $@

%.o: %.c Makefile $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.so

.PHONY: clean
