import { WASI } from "@runno/wasi";

const wasi = new WASI({
    stdout: (out) => console.log("stdout", out),
    stderr: (err) => console.error("stderr", err),
    stdin: () => prompt("stdin:"),
});

(async () => {

    const memory = new WebAssembly.Memory({ initial: 32, maximum: 10000 });

    const wasm = await WebAssembly.instantiateStreaming(
        fetch("./render.wasm"), {
            ...wasi.getImportObject(),
            env: { memory },
        }
    );


    const width = 500;
    const height = 500;
    const stride = 4;
    let buffer = new Uint8Array(width*height*stride);

    const render = wasm.instance.exports.render;
    const buf = render(buffer, width, height);
    const xs = Uint8Array.from(buf);
    console.log(xs);

})()
