#!/bin/sh
set -euxo pipefail

make -C ../yarl web

clang \
wasm.c \
../yarl/libyarl.a \
--sysroot=/usr/share/wasi-sysroot/ \
--target=wasm32-wasi \
-nostdlib \
-nostartfiles \
-Wl,--export-all \
-Wl,--no-entry \
-o render.wasm \
-lc \
-Oz
