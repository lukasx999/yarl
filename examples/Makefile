CFLAGS=-Wall -Wextra -std=c11 -pedantic -O3
LIBS=-lm -lraylib -lX11 -lGL -lglfw

usage:
	@echo "Please specify the name of the example file (without file extension) as the second argument to make."

%: %.c
	cc $(CFLAGS) $< -o $@ ../yarl/libyarl.a -I../yarl $(LIBS)

clean:
	rm ./ppm/*

.PHONY: clean, usage
