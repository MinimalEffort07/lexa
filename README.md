# LeXa
A lexer.

## Dependencies
- cmake
- gcc

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

## Overview
lexa is a lexical analyser. It breaks input files up into lexemes. A lexeme is 
within lexa is defined as a string of alphanumeric characters.
