# CC=cc
CC=~/opt/x86_64/bin/x86_64-elf-gcc
CFLAGS=-ffreestanding -Wall -Wextra -std=c11 -pedantic -ggdb -O0
WEBCC=clang
WEBFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -Og --target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot/ --no-standard-libraries
AR=ar
ARFLAGS=rcs
OBJS=yarl.o
DEPS=yarl.h

static: libyarl.a
shared: libyarl.so
all: shared static test

web: libyarl.a

%.so: $(OBJS)
	@$(CC) $(CFLAGS) $^ -shared -o $@
	@echo "LINK" $^

%.a: $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "AR" $^

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC" $<

clean:
	-rm *.o *.so *.a test

.PHONY: clean, doc
