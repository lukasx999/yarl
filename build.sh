#!/bin/sh
set -euxo pipefail

if [[ $# != 0 && $1 == "live" ]]; then
    find . | entr -cs "sh -c ./build.sh && echo 'Build successful' && time ./main && echo 'Run successful' && kill -SIGHUP $(pidof mupdf)"
else
    make -BC yarl
    cc -c main.c
    cc -static main.o ./yarl/libyarl.a -I./yarl -o main -no-pie -lm
    # ~/opt/x86_64/bin/x86_64-elf-gcc -ffreestanding -I./yarl -o main main.c -nostdlib ./yarl/libyarl.a
    ./main
fi
