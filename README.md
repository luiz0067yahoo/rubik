# ANALISE-DE-ALGORITIMO-GENETICO-USANDO-TECNOLOGIA-WEBASSEMBLY-PARA-SOLUCAO-DO-CUBO-DE-RUBIK
ANALISE DE ALGORÍTIMO GENÉTICO  USANDO TÉCNOLOGIA WEBASSEMBLY PARA SOLUÇÃO DO CUBO DE RUBIK.

demo
https://luiz0067yahoo.github.io/rubik/

Foi possivel establecer a ligação do Java Script com o Código C compilado desta forma

Usada a ferramenta https://wasdk.github.io/WasmFiddle/ .

codigo em C.

    int hello() { 
      return "Hello";
    }

codigo em JS.

    var wasmModule = new WebAssembly.Module(wasmCode);
    var wasmInstance = new WebAssembly.Instance(wasmModule, wasmImports);
    let buffer = new Uint8Array(wasmInstance.exports.memory.buffer); 
    let result = wasmInstance.exports.hello();
    let resultText = ""; 
    for (let i=result; buffer[i]; i++) {
        resultText += String.fromCharCode(buffer[i]);
    }
    log(resultText);

O retorno de cadeia de caracteres não excede 16 unidades.

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


A passagem de parametro somente consegui variavel por variável, sem vetor, sem array ou tipos de dados mais complexos.

Além disso durante o processo de desenvolvimento quando aumentava-se a quantidade de funções gerava um erro:

“Uncaught RangeError: WebAssembly.Compile is disallowed on the main thread, if the buffer size is larger than 4KB. Use WebAssembly.compile, or compile on a worker thread.”
