CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0
WEBCC=clang
WEBFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0 --target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot/ --no-standard-libraries
LIBS=-lm
AR=ar
ARFLAGS=rcs
OBJS=yarl.o
DEPS=yarl.h formats.h

static: libyarl.a
shared: libyarl.so
all: shared static test

# TODO: add conditional for cc flags
CC=$(WEBCC)
CFLAGS=$(WEBFLAGS)
web: libyarl.a


test: test.o static
	@$(CC) $(CFLAGS) $< libyarl.a -o test -lm
	@echo "Building Test Binary..."
	@./test
	@echo "Running tests..."

%.so: $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $^ -shared -o $@
	@echo "LINK" $^

%.a: $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^ $(LIBS)
	@echo "AR" $^

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC" $<

clean:
	-rm *.o *.so *.a test
	-rm -r html/

.PHONY: clean, doc
