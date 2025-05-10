#!/bin/sh
set -euxo pipefail

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
