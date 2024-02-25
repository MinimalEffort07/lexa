#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_FILE_SIZE 10000

int getWordLength(char* word) {
    if(NULL == word)
        return 0;

    char* original = word;

    while(isalpha(*(word++)))
        ;

    return (ptrdiff_t)(word - original) - 1;
}

int main(int argc, char** argv) {

    int ret = -1;

    if(argc != 2) {
        printf("Usage: %s <file to analyse>\n", argv[0]);
        return ret;
    }

    FILE* fileInput = fopen(argv[1], "r");
    if(NULL == fileInput) {
        puts("Failed to open input file");
        return ret;
    }

    if(0 != fseek(fileInput, 0, SEEK_END)) {
        puts("fseek failed?!");
        return ret;
    }

    long sInput = ftell(fileInput);
    if(0 == sInput) {
        puts("File was empty!");
        return ret;
    }

    if(MAX_INPUT_FILE_SIZE <= sInput) {
        puts("File too big!");
        return ret;
    }

    printf("The size of %s is %ld bytes\n", argv[1], sInput);

    // +1 To provide space for the NULL byte
    unsigned char* contentsFile = calloc(sInput + 1, sizeof(unsigned char));
    if(NULL == contentsFile) {
        puts("Out of memory, couldn't read in file contents");
        return ret;
    }

    if(0 != fseek(fileInput, 0, SEEK_SET)) {
        puts("Couldn't reset file position indicator to beginning of file");
        goto contentsFileCleanup;
    }

    size_t nbytesRead = fread(contentsFile, sizeof(char), sInput, fileInput);
    if(sInput != nbytesRead) {
        printf(
        "Mismatch, size of file: %ld,"
        "number of bytes read %lu\n",
        sInput, nbytesRead);
        goto contentsFileCleanup;
    }

    contentsFile[sInput] = '\0';

    size_t nSymbols    = 0;
    char** symbolTable = NULL;

    for(int i = 0; i < (sInput + 1); i++) {
        if(isblank(contentsFile[i]))
            continue;

        if(isalpha(contentsFile[i])) {
            int sWord = getWordLength(&contentsFile[i]);
            if(0 == sWord) {
                puts("Error getting length of symbol");
                goto symbolTableCleanup;
            }

            // printf("SymbolTable before: %p\n", symbolTable);
            symbolTable = reallocarray(symbolTable, ++nSymbols, sizeof(char*));
            if(NULL == symbolTable) {
                puts("Out of memory, couldn't expand symbol table");
                goto symbolTableCleanup;
            }
            // printf("SymbolTable after: %p\n", symbolTable);

            symbolTable[nSymbols - 1] = calloc(sWord + 1, sizeof(char));
            if(NULL == symbolTable[nSymbols - 1]) {
                puts("Out of memory, couldn't allocate symbol in symbol table");
                goto symbolTableCleanup;
            }

            if(NULL == strncpy(symbolTable[nSymbols - 1], &contentsFile[i], sWord + 1)) {
                puts("Failed to copy symbol into symbol table");
                goto symbolTableCleanup;
            }

            symbolTable[nSymbols - 1][sWord] = '\0';
            printf("Symbol stored is: %s\n", symbolTable[nSymbols - 1]);
            i += sWord;
            continue;
        }
    }

    ret = 0;

symbolTableCleanup:
    if(symbolTable) {
        for(int i = 0; i < nSymbols && symbolTable[i]; i++) {
            free(symbolTable[i]);
            symbolTable[i] = NULL;
        }
        free(symbolTable);
    }
contentsFileCleanup:
    if(contentsFile)
        free(contentsFile);
    contentsFile = NULL;

closeFileCleanup:
    if(fileInput)
        fclose(fileInput);

    return ret;
}
