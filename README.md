# LeXa
LeXa (lx) is a Lexical Analyser for the C programming language. It ingests C
source code, breaks words up into lexemes and then outputs tokens of those 
lexemes which contain a Token Name and optionally a Token Attribute.

## Dependencies
- cmake
- gcc
- doxygen

## Building
```bash
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Building with support for clangd
```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS
cmake --build build
```

### Generating Docs
```
doxygen
```

