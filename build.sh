#!/bin/sh
set -euxo pipefail

make -BC yarl
cc main.c -I./yarl -L./yarl -lyarl -Wl,-rpath=./yarl -o main -lraylib
