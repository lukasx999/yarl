CFLAGS=-Wall -Wextra -std=c11 -pedantic -O3 -Ilib -ggdb
LIBS=-lm -lraylib -lX11 -lGL -lglfw -lwayland-client
YARL=../yarl/libyarl.a

usage:
	@echo "Please specify the name of the example file (without file extension) as the second argument to make."

%: %.c Makefile $(YARL)

	@echo "Building dependencies"

	@wayland-scanner private-code \
	< /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
	> lib/xdg-shell-protocol.c

	@wayland-scanner client-header \
	< /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
	> lib/xdg-shell-client-protocol.h

	@make -BC ../yarl
	@echo "Building Yarl library..."
	@cc $(CFLAGS) lib/xdg-shell-protocol.c $< -o $@ $(YARL) -I../yarl $(LIBS)
	@echo "Building example:" $<
	@./$@
	@echo "Running example:" $@
	@rm $@
	@echo "Delete examle:" $@

clean:
	rm gallery/*

.PHONY: clean, usage
