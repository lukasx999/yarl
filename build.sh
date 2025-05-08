#!/bin/sh
set -euxo pipefail

cc main.c -I./yarl -L./yarl -lyarl -Wl,-rpath=./yarl -o main -lraylib
