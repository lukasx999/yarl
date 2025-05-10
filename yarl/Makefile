CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -O0
LIBS=-lraylib -lm
AR=ar
ARFLAGS=rcs
FEATURES=-DYARL_BACKEND_RAYLIB -DYARL_BACKEND_PPM
OBJS=yarl.o backend.o
DEPS=yarl.h

static: libyarl.a
shared: libyarl.so
all: shared static doc test

doc:
	doxygen

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
