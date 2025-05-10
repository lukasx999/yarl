CFLAGS=-Wall -Wextra -std=c11 -pedantic -O3
LIBS=-lm -lraylib

all: examples

examples: examples.c
	@make -C ../yarl static
	@echo Building Library
	@cc $(CFLAGS) $(LIBS) -o examples $< ../yarl/libyarl.a -I../yarl
	@echo Building Examples
	@./examples
	@echo Running Examples

clean:
	rm examples *.ppm

.PHONY: clean
