#!/bin/sh
set -euxo pipefail

if [[ $# != 0 && $1 == "live" ]]; then
    find . | entr -s "sh -c ./build.sh && ./main && kill -SIGHUP $(pidof mupdf)"
else
    make -BC yarl
    cc main.c ./yarl/libyarl.a -I./yarl -o main -lraylib -lm -lX11
fi
