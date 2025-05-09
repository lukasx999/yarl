CFLAGS=-Wall -Wextra -std=c11 -pedantic -O3 $< ../yarl/libyarl.a -I../yarl 
LIBS=-lm -lraylib

all: examples

examples: examples.c
	@make -C ../yarl static
	@echo Building Library
	@cc $(CFLAGS) $(LIBS) -o examples
	@echo Building Examples
	@./examples
	@echo Running Examples

clean:
	rm examples

.PHONY: clean
