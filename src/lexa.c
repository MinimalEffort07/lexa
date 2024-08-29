/* lexa is a lexical analyser for the C programming language. 
 *
 * Lexa reads a C source file, meaningfully groups characters into 'lexemes'
 * and the produces as output a token for each lexeme.
 *
 * Tokens are composed of a:
 * - 'Token Name' which is an abstract symbol used for syntax analysis by the parser 
 * - Pointer into the symbol table to provide additional information about that lexeme.
 */

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Largest accepted input file size in bytes */
#define MAX_INPUT_FILE_SIZE 10000

/**
 * @brief Obtains the length of a lexeme provided its a valid lexeme
 *
 * @param word [in] - lexeme to find length of
 * @param cmpFn [in] - Function pointer used to verify that each byte in the 
 * lexeme from the starting address to the first encounter of a whitespace 
 * character conforms to the requirements of a lexeme. Commonly this will be
 * a function like isdigit(), isalpha(), isalnum() etc. 
 *
 * @return Size of word, if its a valid lexeme or 0 otherwise
 */
int getLexemeLength(char* word, int (*cmpFn)(int character)) {
    if(NULL == word)
        return 0;

    uint32_t count = 0;

    while(word && cmpFn(*word)) {
        word++;
        count++;
    }

    return count;
}

int main(int argc, char** argv) {

    int ret = -1;

    if(2 != argc) {
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
    char* contentsFile = calloc(sInput + 1, sizeof(char));
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

    for(int i = 0; i < sInput; i++) {
        if(isblank(contentsFile[i]))
            continue;

        if(isalpha(contentsFile[i])) {
            int sWord = getLexemeLength(&contentsFile[i], isalpha);
            if(0 == sWord) {
                puts("Error getting length of symbol");
                goto symbolTableCleanup;
            }

            symbolTable = reallocarray(symbolTable, ++nSymbols, sizeof(char*));
            if(NULL == symbolTable) {
                puts("Out of memory, couldn't expand symbol table");
                goto symbolTableCleanup;
            }

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

        } else if(isdigit(contentsFile[i])) {
            int sWord = getLexemeLength(&contentsFile[i], isdigit);
            if(0 == sWord) {
                puts("Error getting length of symbol");
                goto symbolTableCleanup;
            }
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
