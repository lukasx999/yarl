CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -Og
WEBCC=clang
WEBFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -Og --target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot/ --no-standard-libraries
AR=ar
ARFLAGS=rcs
OBJS=yarl.o
DEPS=yarl.h formats.h

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
