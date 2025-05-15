CFLAGS=-Wall -Wextra -std=c11 -pedantic -O3
LIBS=-lm -lraylib -lX11 -lGL -lglfw
YARL=../yarl/libyarl.a

usage:
	@echo "Please specify the name of the example file (without file extension) as the second argument to make."

%: %.c Makefile $(YARL)
	@make -C ../yarl
	@echo "Building Yarl library..."
	@cc $(CFLAGS) $< -o $@ $(YARL) -I../yarl $(LIBS)
	@echo "Building example:" $<
	@./$@
	@echo "Running example:" $@
	@rm $@
	@echo "Delete examle:" $@

clean:
	rm gallery/*

.PHONY: clean, usage
