#!/bin/sh
set -euxo pipefail

make -BC yarl
cc main.c ./yarl/libyarl.a -I./yarl -o main -lraylib -lm -lX11
