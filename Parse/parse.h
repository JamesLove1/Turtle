#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #define  NDEBUG
#include <assert.h>
#include <math.h>

#define MAXNUMTOKENS 20
#define TOKENMAXLEN 20
#define MAXINPUTS 2
#define LEN 2

typedef struct script {
    char** wordArray;
    int maxLen;
    int index;
    char prevInstruction[15];
    char errorMessage[200];
} script;

void test(void);

script* init_script(void);
void init_wordArray(script* script);
void addWord(script* script);
void loadWords(script* script, FILE* TLLs);
void freeWordArray(script* script);
void free_script(script* x);

bool PROG(script* file);
bool INSLST(script* file);
bool INS(script* file);
bool FWD(script* file);
bool RGT(script* file);
bool NUM(script* file);
bool COL(script* file);
bool LOOP(script* file);
bool SET(script* file);
bool VARNUM(script* file);
bool VAR(script* file);
bool LTR(script* file);
bool WORD(script* file);
bool LST(script* file);
bool ITEMS(script* file);
bool ITEM(script* file);
bool PFIX(script* file);
bool OP(script* file);
