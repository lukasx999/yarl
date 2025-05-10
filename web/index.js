(async () => {

    // TODO: install wasmer npm package

    const wasm = await WebAssembly.instantiateStreaming(
        fetch("./render.wasm"),
        {wasi_snapshot_preview1: {}}
    );
    console.log(wasm);
})()
