#include"./parse.h"

int main(int argc, char* argv[]){ 
  test();
  int inputNotGraterThanOne = MAXINPUTS;
  if(argc > inputNotGraterThanOne){
      exit(EXIT_FAILURE);
  }
  FILE* TLLs = fopen(argv[1],"r");
  if(TLLs == NULL){
    fprintf(stderr,"TTLS FILE PATH IS INCORRECT\n\n");
    exit(EXIT_FAILURE);
  }
  script* script = init_script();
  init_wordArray(script);
  loadWords(script, TLLs);
  if(!PROG(script)){
    fprintf(stderr,"%s\n",script->errorMessage);
    freeWordArray(script);
    free_script(script);
    fclose(TLLs); 
    exit(EXIT_FAILURE);
  }
  fclose(TLLs);
  freeWordArray(script);
  free_script(script);
  return EXIT_SUCCESS;
}

void loadWords(script* script, FILE* TLLs){
  while(fscanf(TLLs,"%s",script->wordArray[script->index]) == 1){     
      addWord(script);
      script->index++;
    } 
    script->index = 0;
}

void init_wordArray(script* script){
  int initalSize = 1;
  script->maxLen = initalSize;
  script->wordArray = (char**)calloc(initalSize,sizeof(script->wordArray)); 
  if(script->wordArray == NULL){
    fprintf(stderr,"Memmory allocation for script->newTokens failed\n");
  }
  initalSize--;
  script->wordArray[initalSize] = (char*)calloc(TOKENMAXLEN,sizeof(char));
  if(script->wordArray[initalSize] == NULL){
    fprintf(stderr,"Memmory allocation for script->newTokens failed\n");
  }
}

void addWord(script* script){
  int newSize = ++script->maxLen;
  char** tempary = (char**)realloc(script->wordArray,newSize * sizeof(char*)); 
  if(tempary == NULL){
    fprintf(stderr,"Memmory allocation for script->newTokens failed\n");
  }
  script->wordArray = tempary;
  newSize--;
  script->wordArray[newSize] = (char*)calloc(TOKENMAXLEN,sizeof(char));
  if(script->wordArray[newSize] == NULL){
    fprintf(stderr,"Memmory allocation for script->newTokens failed\n");
  }
}

void freeWordArray(script* script){
  for(int i = 0; i < script->maxLen; i++){
    free(script->wordArray[i]);
  }
  script->maxLen = 0;
  free(script->wordArray);
}

script* init_script(void){
  script* array = NULL;
  array = (script*)calloc(1,sizeof(script));
  return array;
}

void free_script(script* x){
  free(x);
}

bool PROG(script* file){
  if(strcmp(file->wordArray[file->index],"START") != 0){
    strcpy(file->errorMessage,"0 Error");
    return false;
  } else {
    file->index++;    
    if(!INSLST(file)){
      return false;
    }
  }
  return true;
}

bool INSLST(script* file){
  if(strcmp(file->wordArray[file->index],"END") == 0){
    return true;
  } 
  if(INS(file)){   
    if(file->index < file->maxLen){
      file->index++;
      if(INSLST(file)){
        return true;
      }
    } else {
      strcpy(file->errorMessage,"1a Error");
      return false;
    }
  }
  strcpy(file->errorMessage,"1b Error");
  return false;
}

bool INS(script* file){
  if(FWD(file)){
    return true;
  }
  if(RGT(file)){
    return true;
  }
  if(COL(file)){
    return true;
  }
  if(LOOP(file)){
    return true;
  }
  if(SET(file)){
    return true;
  }
  strcpy(file->errorMessage,"2 Error");
  return false;
}

bool FWD(script* file){
  bool FWD = strcmp(file->wordArray[file->index],"FORWARD");
  if(FWD == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(VARNUM(file)){ 
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"3 Error");
  return false;
}

bool RGT(script* file){
  bool RGT = strcmp(file->wordArray[file->index],"RIGHT");
  if(RGT == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(VARNUM(file)){ 
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"4 Error");
  return false;
}

bool COL(script* file){
  bool COL = strcmp(file->wordArray[file->index],"COLOUR");
  if(COL == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(VAR(file)){
        return true;
      }
      if(WORD(file)){ 
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"5 Error");
  return false;
}

bool LOOP(script* file){
  bool LOOP = strcmp(file->wordArray[file->index],"LOOP");
  if(LOOP == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(LTR(file)){ 
        file->index++;
        if(file->index < file->maxLen){
          bool OVER = strcmp(file->wordArray[file->index],"OVER");
          if(OVER == 0){
            file->index++;
            if(file->index < file->maxLen){
              if(LST(file)){ 
                file->index++;
                if(file->index < file->maxLen){
                  if(INSLST(file)){
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  strcpy(file->errorMessage,"6 Error");
  return false;
}

bool SET(script* file){
  bool SET = strcmp(file->wordArray[file->index],"SET");
  if(SET == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(LTR(file)){
        file->index++;
        if(file->index < file->maxLen){
          bool leftBracket = strcmp(file->wordArray[file->index],"(");
          if(leftBracket == 0){
            file->index++;
            if(file->index < file->maxLen){
              if(PFIX(file)){
                return true;
              }
            }
          }
        }
      }
    }
  }
  strcpy(file->errorMessage,"7 Error");
  return false;
}

bool VARNUM(script* file){
  if(VAR(file)){
    return true;
  }
  if(NUM(file)){
    return true;
  }
  strcpy(file->errorMessage,"8 Error");
  return false;
}

bool VAR(script* file){
  int DollarSymbol = 0 ;
  if(file->wordArray[file->index][DollarSymbol] == '$'){
    strcpy(file->prevInstruction,"VAR");
    if(LTR(file)){
      return true;
    }
  }
  strcpy(file->errorMessage,"9 Error");
  return false;
}

bool LTR(script* file){
  int lenght = strlen(file->wordArray[file->index]);
  if(!strcmp(file->prevInstruction,"VAR") && lenght == LEN){
    char Dollar[TOKENMAXLEN] = {'\0'};
    char noDollar[TOKENMAXLEN] = {'\0'};
    sscanf(file->wordArray[file->index],"%c%c",Dollar,noDollar); 
    int LTRLenPrev = strlen(noDollar);
    int LTRUpperPrev = isupper(noDollar[LTRLenPrev-1]);
    if(LTRLenPrev == 1 && LTRUpperPrev > 0){
      strcpy(file->prevInstruction,"");
      return true;
    }
  }
  int LTRLen = strlen(file->wordArray[file->index]);
  int LTRUpper = isupper(file->wordArray[file->index][LTRLen-1]);
  if(LTRLen == 1 && LTRUpper > 0){
    return true;
  }
  strcpy(file->errorMessage,"10 Error");
  return false;
}

bool NUM(script* file){
  double num = 0;
  char extraChar = '\0';
  int numItems = sscanf(file->wordArray[file->index],"%lf%c",&num, &extraChar);
  if(numItems == 1 && extraChar == '\0'){
    return true;
  }
  strcpy(file->errorMessage,"11 Error");
  return false;
}

bool WORD(script* file){
  char colour[TOKENMAXLEN] = {'\0'};
  char colourOne[TOKENMAXLEN] = {'\0'};
  int numItems = sscanf(file->wordArray[file->index],"%s %s",colour,colourOne);  
  if(numItems == 1){
    if(strcmp(colour,"\"BLACK\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"RED\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"GREEN\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"BLUE\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"YELLOW\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"CYAN\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"MAGENTA\"") == 0){
      return true;
    }
    if(strcmp(colour,"\"WHITE\"") == 0){
      return true;
    }
  }
  strcpy(file->errorMessage,"12 Error");
  return false;
}

bool LST(script* file){
  bool leftBrace = strcmp(file->wordArray[file->index],"{");
  if(leftBrace == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(ITEMS(file)){
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"13 Error");
  return false;
}

bool ITEMS(script* file){
  bool rightBrace = strcmp(file->wordArray[file->index],"}");
  if(rightBrace == 0){
    return true;
  }
  if(ITEM(file)){
    file->index++;
    if(file->index < file->maxLen){
      if(ITEMS(file)){
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"14 Error");
  return false;
}

bool ITEM(script* file){
  if(VARNUM(file)){
    return true;
  }
  if(WORD(file)){
    return true;
  }
  strcpy(file->errorMessage,"15 Error");
  return false;
}

bool PFIX(script* file){
  bool rightBracket = strcmp(file->wordArray[file->index],")");
  if(rightBracket == 0){
    return true;
  }
  if(OP(file)){
    file->index++;
    if(file->index < file->maxLen){
      if(PFIX(file)){
        return true;
      }
    }  
  }
  if(VARNUM(file)){
    file->index++;
    if(file->index < file->maxLen){
      if(PFIX(file)){
        return true;
      }
    }  
  }
  strcpy(file->errorMessage,"16 Error");
  return false;
}

bool OP(script* file){
  bool equals = strcmp(file->wordArray[file->index],"=");
  if(equals == 0){
    return true;
  }
  bool plus = strcmp(file->wordArray[file->index],"+");
  if(plus == 0){
    return true;
  }
  bool minus = strcmp(file->wordArray[file->index],"-");
  if(minus == 0){
    return true;
  }
  bool divide = strcmp(file->wordArray[file->index],"/");
  if(divide == 0){
    return true;
  }
  bool times = strcmp(file->wordArray[file->index],"*");
  if(times == 0){
    return true;
  }
  strcpy(file->errorMessage,"17 Error");
  return false;
}

