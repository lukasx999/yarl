# Yarl

Platform agnostic 2D rasterization library.

## Implemented Primitives

- Rectangle
- Triangle
- Arc
- Circle
- Line

## Primitives - TODO
- Ellipse
- Text

## Implemented Backends
- OpenGL
- Wayland
- Xlib
- PNG
- PPM
- Raylib

## Backends - TODO
- Rust wgpu
- WASM HTML5 canvas
- Vulkan
- Cairo
- Skia
- SDL
- PDF

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
