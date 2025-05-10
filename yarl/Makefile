CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0
LIBS=-lm
AR=ar
ARFLAGS=rcs
OBJS=yarl.o
DEPS=yarl.h
WEBCC=clang
WEBFLAGS=--target=wasm32-wasi --sysroot=/usr/share/wasi-sysroot/ --no-standard-libraries

static: libyarl.a
shared: libyarl.so
all: shared static doc test

doc:
	doxygen

web:
	$(WEBCC) $(WEBFLAGS) $(FEATURES) -c yarl.c -o yarl.o
	$(AR) $(ARFLAGS) libyarl.a yarl.o

test: test.o static
	@$(CC) $(CFLAGS) $< libyarl.a -o test -lm
	@echo "Building Test Binary..."
	@./test
	@echo "Running tests..."

%.so: $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $^ -shared -o $@
	@echo "LINK" $^

%.a: $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "AR" $^

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) $(FEATURES) -c $< -o $@
	@echo "CC" $<

clean:
	-rm *.o *.so *.a test
	-rm -r html/

.PHONY: clean, doc
