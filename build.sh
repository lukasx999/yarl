#!/bin/sh
set -euxo pipefail

cc main.c yarl.c -Wall -Wextra -std=c11 -pedantic -ggdb -o yarl -lraylib -lm
