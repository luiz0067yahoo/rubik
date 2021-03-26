# ANALISE-DE-ALGORITIMO-GENETICO-USANDO-TECNOLOGIA-WEBASSEMBLY-PARA-SOLU-O-DO-CUBO-DE-RUBIK
ANALISE DE ALGORÍTIMO GENÉTICO  USANDO TÉCNOLOGIA WEBASSEMBLY PARA SOLUÇÃO DO CUBO DE RUBIK
Foi possivel establecer a ligação do Java Script com o Código C compilado desta forma

Usada a ferramenta https://wasdk.github.io/WasmFiddle/

codigo em C.
    int hello() { 
      return "Hello";
    }

codigo em JS
var wasmModule = new WebAssembly.Module(wasmCode);
var wasmInstance = new WebAssembly.Instance(wasmModule, wasmImports);
let buffer = new Uint8Array(wasmInstance.exports.memory.buffer); 
let result = wasmInstance.exports.hello();
let resultText = ""; 
    for (let i=result; buffer[i]; i++) {
       resultText += String.fromCharCode(buffer[i]);
    }
    log(resultText);

Outro exemplo comparametro.

codigo em C.
    int sum(int number1,int number2) { 
      return number1+number2;
    }

codigo em JS.
    var wasmModule = new WebAssembly.Module(wasmCode);
    var wasmInstance = new WebAssembly.Instance(wasmModule, wasmImports);
    let buffer = new Uint8Array(wasmInstance.exports.memory.buffer); 
    var number1=1;
    var number2=2;
    let result = wasmInstance.exports.sum(number1,number2);
    log(result);
