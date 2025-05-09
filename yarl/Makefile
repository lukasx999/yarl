CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0 $(FEATURES)
LIBS=-lraylib -lm
AR=ar
ARFLAGS=rcs
FEATURES=-DYARL_BACKEND_RAYLIB -DYARL_BACKEND_PPM
OBJS=yarl.o backend.o
DEPS=yarl.h

all: shared static

shared: libyarl.so
static: libyarl.a

%.so: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -shared -o $@

%.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c Makefile $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.so *.a

.PHONY: clean
