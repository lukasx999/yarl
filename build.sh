#!/bin/sh
set -euxo pipefail

if [[ $# != 0 && $1 == "live" ]]; then
    find . | entr -cs "sh -c ./build.sh && echo 'Build successful' && time ./main && echo 'Run successful' && kill -SIGHUP $(pidof mupdf)"
else
    make -BC yarl
    cc main.c ./yarl/libyarl.a -I./yarl -o main -lm
    ./main
fi
