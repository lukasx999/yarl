# Yarl

Platform agnostic 2D rasteriztation library.

## Implemented Primitives

- Rectangle
- Triangle
- Arc
- Circle
- Line

## Implemented Backens
- OpenGL
- PPM
- PNG
- Xlib
- Raylib

## Build Instructions

```console
$ git clone --depth 1 https://github.com/lukasx999/yarl.git
$ cd yarl/
$ make <flags>
```

### Available build flags:
- `static` (*default*)
- `shared`
- `doc` (requires `doxygen`)
- `test`
- `web` (requires `wasi-libc`)
