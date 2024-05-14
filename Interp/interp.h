#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #define  NDEBUG
#include <assert.h>
#include <math.h>
#include "../neillsimplescreen.h"

#define MAXNUMTOKENS 20
#define TOKENMAXLEN 20

#define ROWS 33
#define COLS 51 
#define PREVINSTRUCTIONSIZE 15
#define ERRORMESSAGELENGTH 200
#define LEN_OUTPUTFILENAME 200
#define LENVARABLES 26
#define INTMIN 10
#define STACKLENGHT 100
#define POSTSCRIPTCOLOURLEN 30
#define COMMANDLINEINSTRUCTIONLEN 100
#define STACKMUTIPLE 10

#define INPUTSEQUAL 3
#define INPUTONE 1
#define INPUTTWO 2
#define TURTELXINITALVALUE 25
#define TURTELYINITALVALUE 16
#define INDEXOFSET 4
#define OFSET 3
#define DESTINATION 7  
#define SECONDS 0.5
#define THREESIXTYDEGREES 360

#define POSTSCRIPTTURTLEX 30
#define POSTSCRIPTTURTLEY 40
#define POSTSCRIPTARRAYLEN 10

#define M_PI 3.14159265358979323846
#define DEG_TO_RAD (M_PI / 180.0) 

typedef enum symbol {
    EQUAL,
    PLUS,
    MINUS,
    DIVIDE,
    TIMES
} symbol; 

typedef enum outputDataType {
    TXT,
    PS,
    PDF,
    ASCII,
    TESTING
} outputDataType; 

typedef enum VarablesType {
    NONE,
    WORDCOLOUR,
    NUMBER
} VarablesType;

typedef struct VARABLES {
    VarablesType VARType;
    char WORDCOLOUR[TOKENMAXLEN];
    double NUMBER;
} VARABLES;

typedef struct Stack{
    int indexStack;
    int maxLen;
    double stackArray[STACKLENGHT];
} Stack; 

typedef struct dataPostScript{
    double x_moveto;
    double y_moveto;  
    double x_lineto;
    double y_lineto;
    char colour; 
} dataPostScript;

typedef struct postScript {
    dataPostScript* data;
    int maxIndexPostScipt;
    int indexPostScript;
    double postScript_X;
    double  postScript_Y;
} PostScript; 

typedef struct script {   
    //Parsing
    char** wordArray;
    int maxLen;
    int index;
    char prevInstruction[PREVINSTRUCTIONSIZE];
    char errorMessage[ERRORMESSAGELENGTH];
    // Interpreting Tuttle
    char screen[ROWS][COLS];
    double turtle_X;
    double turtle_Y;
    double turtle_Degrees;
    char turtle_Colour;
    int X_draw;
    int Y_draw;
    //output
    outputDataType outputType;
    char outputFileName[LEN_OUTPUTFILENAME];
    //varables
    VARABLES VARArray[LENVARABLES];
    //stack
    Stack stack;
    //postscript
    PostScript postScript;
} script;

void test(void);

script* init_script(void);
void init_turtle(script* script);
void witchOutput(script* x, char *argvTwo);
void Output(script* script);
void convertToPDF(script* script);
void ASCII_Screen(script* script);
void ifPSsetTurtle(script* script);
void textFile(script* script);
void toPDF(script* script);
void init_wordArray(script* script);
void addWord(script* script);
void loadWords(script* script, FILE* TLLs);
void drawingCordinates(script *s, double distance);
void drawLine(script* script, double distance);
int  endElement(script* file);
void wordOrNum(script* file, int LTRindex, int LSTindex);
void isNUM(script* file, int varable, int withinCurlyBrackets);
void isWORD(script* file, int IndexVARArray, int IndexWordArray);
bool isVARCOLOUR(script* file, int index);
bool isValidNUM(script *file, int index);
bool MaxIndexGraterThanIndex(script* file, char errorMessage[ERRORMESSAGELENGTH]);
void addDataPostScript(script* PROG, double x_moveto, double y_moveto, double x_lineto, double y_lineto);
void postScriptOutput(script* script);
void toRGBcolour(char colour, char RGBcolour[POSTSCRIPTCOLOURLEN]);
void freeWordArray(script* script);
void free_script(script* x);

bool PROG(script* file);
bool INSLST(script* file);
bool INS(script* file);
bool FWD(script* file);
void FWD_Interp(script* file);
bool RGT(script* file);
void RGT_Interp(script* file);
bool NUM(script* file);
bool COL(script* file);
void COL_Interp(script* file);
void COL_Interp_Vars(script* file);
char colourToChar(char colour[TOKENMAXLEN]);
bool LOOP(script* file);
void LOOPInterp(script* file);
int  indexStartLoop(script* file);
bool SET(script* file);
bool VARNUM(script* file);
bool VAR(script* file);
void init_VARArray(script* file);
int  LTRToVarArrayIndex(char LTRCharacter);
void VAR_Interp(script* file);
bool LTR(script* file, int* LTRindex);
bool WORD(script* file);
bool LST(script* file, int* leftBracePointer);
bool ITEMS(script* file);
bool ITEM(script* file);
bool PFIX(script* file, int indexLTR);
bool OP(script* file);
void evaluatePostfix(script* file, int symbol);

void push(script* prog, double number);
void pushStr(script* prog, char pushValue[TOKENMAXLEN]);
double pop(script* prog);
void setVAR(script* prog, int indexLTR);
void resetStack(script* prog);

