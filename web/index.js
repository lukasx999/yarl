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


    const width = 300;
    const height = width;
    const stride = 4;
    let buf = new Uint8ClampedArray(width*height*stride);
    for (let i=0; i < buf.length; ++i) {
        buf[i] = 100;
    }

    const render = wasm.instance.exports.render;
    render(buf, width, height);

    // document.getElementById("img").src = URL.createObjectURL(
    //     new Blob([buf.buffer], { type: 'image/png' })
    // );

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");

    let imageData = new ImageData(buf, width);
    ctx.putImageData(imageData, 20, 20);


})()
