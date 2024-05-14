#include"./extension.h"

int main(int argc, char* argv[]){ 
  test();
  int inputNotGraterThanOne = INPUTSIZE;
  if(argc > inputNotGraterThanOne){
    exit(EXIT_FAILURE);
  }
  FILE* TLLs = fopen(argv[ARGVONE],"r");
  if(TLLs == NULL){
    fprintf(stderr,"TTLS FILE PATH IS INCORRECT\n");
    exit(EXIT_FAILURE);
  }
  script* script = init_script();
  init_turtle(script);
  init_wordArray(script);
  loadWords(script, TLLs);
  if(argv[ARGVTWO] != NULL){
    strcpy(script->outputFileName,argv[ARGVTWO]);
  }
  witchOutput(script, argv[ARGVTWO]);
  if(script->outputType != TTL){   
    ifPSsetTurtle(script);
    if(!PROG(script)){
      fprintf(stderr,"%s\n",script->errorMessage);
      freeWordArray(script);
      free_script(script);
      fclose(TLLs);
      exit(EXIT_FAILURE);
    }
    Output(script);
    toPDF(script);
  }
  if(script->outputType == TTL){
    Output(script);
  }
  fclose(TLLs);
  freeWordArray(script);
  free_script(script);
  return EXIT_SUCCESS;
}

void toPDF(script* script){
  if(script->outputType == PS){
    char command[COMMANDLINEINSTRUCTIONLEN] = "";
    strcat(command,"ps2pdf ");
    strcat(command,script->outputFileName);
    system(command);
  }
}

void extension(script* script){ 
  extensionInstructions();
  char in = ' ';
  strcpy(script->wordArray[script->index],"START");
  bool pastInstruction = false;
  while (in != 'q'){
    in = getchar(); 
    // rotation & forwards
    if(in == 'w' && in != 'e'){
      extension_RGTandFWD(script, 'w', pastInstruction);
      pastInstruction = true;   
    }
    if(in == 's' && in != 'e'){
      extension_RGTandFWD(script, 's', pastInstruction);
      pastInstruction = true;       
    }
    if(in == 'a' && in != 'e'){
      extension_RGTandFWD(script, 'a', pastInstruction);
      pastInstruction = true;   
    }
    if(in == 'd' && in != 'e'){
      extension_RGTandFWD(script, 'd', pastInstruction);
      pastInstruction = true;   
    }
    //colurs
    if(in == 'k' && in != 'e'){
      extension_RGTandFWD(script, 'k', pastInstruction);
      pastInstruction = true;   
    }
    if(in == 'r' && in != 'e'){
      extension_RGTandFWD(script, 'r', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'g' && in != 'e'){
      extension_RGTandFWD(script, 'g', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'y' && in != 'e'){
      extension_RGTandFWD(script, 'y', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'b' && in != 'e'){
      extension_RGTandFWD(script, 'b', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'm' && in != 'e'){
      extension_RGTandFWD(script, 'm', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'c' && in != 'e'){
      extension_RGTandFWD(script, 'c', pastInstruction);
      pastInstruction = true; 
    }
    if(in == 'h' && in != 'e'){
      extension_RGTandFWD(script, 'h', pastInstruction);
      pastInstruction = true;   
    }
    // reset values
    for(int rows = 0; rows < ROWS; rows++){
      for(int colls = 0; colls < COLS; colls++){
      script->screen[rows][colls] = ' ';
      }
    }
    script->turtle_X = INITALTURTLEX;
    script->turtle_Y = INITALTURTLEY;
    script->X_draw = 0;
    script->Y_draw = 0;
    script->index = 0;
    script->turtle_Colour = 'W';
    script->turtle_Degrees = 0;
    //PROG
    if(in > 0){
      PROG(script);
    }
    ASCII_Screen(script);
    extensionInstructions();
  }
  extensionOutput(script);
}

void extensionInstructions(void){
    printf("\033[1m\033[4mInstructions\033[0m\n");
    printf("Type a single letter char to the teminal press \nenter to execute each instruction\n");
    printf("\n\033[1mOutput TTL file and quit program - q\033[0m\n\n");
    
    printf("\033[4mFWD & Rotation\033[0m\n");
    printf("FWD 1 square & Rotate 0 Degrees   - w\n");
    printf("Rotate 90 Degrees                 - d\n");
    printf("Rotate 180 Degrees                - s\n");
    printf("Rotate 270 Degrees                - a\n");
    printf("(Degrees is cumlitivaly added - make sure to press w \nbetween rotations)\n");

    printf("\n\033[4mColours\033[0m\n");
    printf("black   - k\n");
    printf("red     - r\n");
    printf("green   - g\n");
    printf("yellow  - y\n");
    printf("blue    - b\n");
    printf("magenta - m\n");
    printf("cyan    - c\n");
    printf("white   - h\n");
    printf("\n>>");
}

void extension_RGTandFWD(script* script,char letter, bool pastInstruction){
  switch (letter){
  case 'w':
    if(!pastInstruction){
      script->index++;
      addWord(script);
    } 
    script->turtle_Degrees = 0;
    strcpy(script->wordArray[script->index],"RIGHT");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"0");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"FORWARD");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"1");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 's':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    script->turtle_Degrees = 0;
    strcpy(script->wordArray[script->index],"RIGHT");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"180");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"FORWARD");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"1");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'a':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    script->turtle_Degrees = 0;
    strcpy(script->wordArray[script->index],"RIGHT");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"270");    
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"FORWARD");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"1");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'd':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    script->turtle_Degrees = 0;
    strcpy(script->wordArray[script->index],"RIGHT");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"90");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"FORWARD");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"1");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'k':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    }  
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"BLACK\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'r':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"RED\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'g':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"GREEN\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'y':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"YELLOW\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'b':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"BLUE\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'm':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"MAGENTA\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'c':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"CYAN\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  case 'h':
    if(!pastInstruction){
      addWord(script);
      script->index++;
    } 
    strcpy(script->wordArray[script->index],"COLOUR");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"\"WHITE\"");
    addWord(script);
    script->index++;
    strcpy(script->wordArray[script->index],"END");
    break;
  default:
    break;
  }
}

void extensionOutput(script* script){ 
  FILE* ttlFile = fopen(script->outputFileName,"w");
  script->index = 0;
  fprintf(ttlFile,"%s \n",script->wordArray[script->index]);
  script->index++;  
  for(int i = 1; i < script->maxLen-1; i++){
    fprintf(ttlFile,"%s %s \n",script->wordArray[i], script->wordArray[i+1]);  
    i++;
  }
  fprintf(ttlFile,"%s \n","END");
  fclose(ttlFile);
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
  array->stack.maxLen = STACKLENGHT;
  array->stack.indexStack = 0;
  int size = POSTSCRIPTSIZE;
  array->postScript.data = (dataPostScript*)calloc(size,sizeof(dataPostScript));
  array->postScript.indexPostScript = 0;
  array->postScript.maxIndexPostScipt = size; 
  return array;
}

void init_turtle(script* script){
  script->turtle_Degrees = 0;
  script->turtle_Colour = 'W';
  script->turtle_X = INITALTURTLEX;
  script->turtle_Y = INITALTURTLEY;
  script->outputType = TESTING;
  for(int rows = 0; rows < ROWS; rows++){
    for(int colls = 0; colls < COLS; colls++){
      script->screen[rows][colls] = ' ';
    }
  }
}

void free_script(script* x){
  free(x->postScript.data);
  free(x);
}

void drawLine(script* script, int distance){  
  if(script->outputType == PS){
    double x_moveto = script->turtle_X;
    double y_moveto = script->turtle_Y;
    drawingCordinates(script, distance);
    double x_lineto = script->postScript.postScript_X;
    double Y_lineto = script->postScript.postScript_Y;
    script->turtle_X = script->postScript.postScript_X;
    script->turtle_Y = script->postScript.postScript_Y;
    addDataPostScript(script,x_moveto,y_moveto,x_lineto,Y_lineto);
    return;
  }
  for(int count = 0; count <= distance; count++){
    drawingCordinates(script, count);
    int x = script->X_draw;
    int y = script->Y_draw;
    char colour = script->turtle_Colour;
    //2D-Array
    if(x >= 0 && y >= 0 && x < COLS && y < ROWS ){
      script->screen[y][x] = colour;
    }
  } 
  script->turtle_X = script->X_draw;
  script->turtle_Y = script->Y_draw;
  return;
}

void drawingCordinates(script* script, double distance){
  //TRIG
  double angleInRadians = script->turtle_Degrees * DEG_TO_RAD;
  double deltaX = distance * sin(angleInRadians); 
  double deltaY = -distance * cos(angleInRadians);
  if(script->outputType == PS){
    script->postScript.postScript_X = script->turtle_X + deltaX;
    script->postScript.postScript_Y = script->turtle_Y - deltaY;
    return;
  }
  //2D-Array 
  script->X_draw = (int)round(script->turtle_X+deltaX);
  script->Y_draw = (int)round(script->turtle_Y+deltaY);
  return;
}

void addDataPostScript(script* PROG, double x_moveto, double y_moveto, double x_lineto, double y_lineto){
  int maxIndexPS = PROG->postScript.maxIndexPostScipt;
  int newIndexMax = maxIndexPS+POSTSCRIPTSIZE;
  int newSize = (newIndexMax) * sizeof(dataPostScript);
  if(PROG->postScript.indexPostScript >= maxIndexPS){
    dataPostScript* temp = (dataPostScript*)realloc(PROG->postScript.data, newSize);
    if(temp == NULL){
      fprintf(stderr,"Memmory allocation for PROG->postScript.data failed\n");
    } 
    PROG->postScript.data = temp;
    PROG->postScript.maxIndexPostScipt = newIndexMax;
  }
  int index = PROG->postScript.indexPostScript;
  char colour = PROG->turtle_Colour;
  PROG->postScript.data[index].colour = colour;  
  PROG->postScript.data[index].x_lineto = x_lineto;
  PROG->postScript.data[index].y_lineto = y_lineto;
  PROG->postScript.data[index].x_moveto = x_moveto;
  PROG->postScript.data[index].y_moveto = y_moveto; 
  PROG->postScript.indexPostScript++;
}

void witchOutput(script* script, char *argvTwo){ 
  script->outputType = ASCII;
  if(argvTwo!= NULL){
    int indexOffset = strlen(argvTwo) - FOUR;
    int numCharacters = FOUR;
    char destination[DESTINATION] = {'\0'};
    if(indexOffset >= 0){
      strncpy(destination,argvTwo+indexOffset,numCharacters);
      if(strcmp(destination,".txt")==0){
        script->outputType = TXT;
      }
      if(strcmp(destination,".pdf")==0){
        script->outputType = PDF;
      }
      if(strcmp(destination,".ttl")==0){
        script->outputType = TTL;
      }
    }
    indexOffset = strlen(argvTwo) - INPUTSIZE;
    numCharacters = INPUTSIZE;
    char destinationOne[100] = {'\0'};
    if(indexOffset >= 0){
      strncpy(destinationOne,argvTwo+indexOffset,numCharacters);
      if(strcmp(destinationOne,".ps")==0){
        script->outputType = PS;
      }
    }
    if(strcmp(argvTwo,"TESTING")==0){
      script->outputType = TESTING;
    }
  }
}

void Output(script* script){
  switch (script->outputType){
    case TXT:
      textFile(script);
      break;
    case PS:
      postScriptOutput(script);
      break;
    case PDF:
      toPDF(script);
      break;
    case ASCII:
      ASCII_Screen(script);
      break;
    case TESTING:
      break;
    case TTL:
      extension(script); 
      break;
    default:
      printf("Error-witchOutput");
      break;
  }
}

void ASCII_Screen(script* script){
  neillclrscrn(); 
  neillbgcol(black);
  neillcursorhome();
  double seconds = SECONDS;
  for(int rows = 0; rows < ROWS; rows++){
    for(int colls = 0; colls < COLS; colls++){
      if(script->screen[rows][colls] == 'K'){
        neillfgcol(black);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'R'){
        neillfgcol(red);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'G'){
        neillfgcol(green);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'Y'){
        neillfgcol(yellow);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'B'){
        neillfgcol(blue);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'M'){
        neillfgcol(magenta);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'C'){
        neillfgcol(cyan);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == 'W'){
        neillfgcol(white);
        printf("%c",script->screen[rows][colls]);   
      }
      if(script->screen[rows][colls] == ' '){
        printf("%c",script->screen[rows][colls]);   
      }
    }
    printf("\n");
  }
  if(script->outputType != TTL){
    neillbusywait(seconds);
  }
  neillreset();
}

void ifPSsetTurtle(script* script){
  if(script->outputType == PS){
    script->turtle_X = PSTURTLEX;
    script->turtle_Y = PSTURTLEY;
  }
}

void textFile(script* script){
  FILE* textFile = fopen(script->outputFileName,"w");
  for(int rows = 0; rows < ROWS; rows++){
    for(int colls = 0; colls < COLS; colls++){
      fprintf(textFile,"%c",script->screen[rows][colls]);
    }
    fprintf(textFile,"\n");
  }
  fclose(textFile);
}

void postScriptOutput(script* script){
  FILE* postScriptFile = fopen(script->outputFileName,"w");
  fprintf(postScriptFile,"%s","0.2 setlinewidth\n");
  fprintf(postScriptFile,"%s","10 10 scale\n");
  for(int i = 0; i < script->postScript.maxIndexPostScipt; i++){
    fprintf(postScriptFile,"%s","newpath\n");
    double moveTo_x = script->postScript.data[i].x_moveto;
    double moveTo_y = script->postScript.data[i].y_moveto; 
    fprintf(postScriptFile,"%f %f moveto\n",moveTo_x,moveTo_y);
    double lineTo_x = script->postScript.data[i].x_lineto;
    double lineTo_y = script->postScript.data[i].y_lineto;
    fprintf(postScriptFile,"%f %f lineto\n",lineTo_x,lineTo_y);
    char colour = script->postScript.data[i].colour;
    char RGBcolour[POSTSCRIPTCOLOURLEN] = "";
    toRGBcolour(colour, RGBcolour);
    fprintf(postScriptFile,"%s setrgbcolor\n",RGBcolour);
    fprintf(postScriptFile,"%s","stroke\n");
  }  
  fprintf(postScriptFile,"%s","showpage\n");
  fclose(postScriptFile);
}

void toRGBcolour(char colour, char RGBcolour[POSTSCRIPTCOLOURLEN]){
  if(colour == 'K'){
    strcpy(RGBcolour,"0 0 0");
    return;
  }
  if(colour == 'R'){
    strcpy(RGBcolour,"1 0 0");
    return;
  }
  if(colour == 'G'){
    strcpy(RGBcolour,"0 1 0");
    return;
  }
  if(colour == 'Y'){
    strcpy(RGBcolour,"1 1 0"); 
    return;
  }
  if(colour == 'B'){
    strcpy(RGBcolour,"0 0 1");
    return;
  }
  if(colour == 'M'){
    strcpy(RGBcolour,"1 0 1");
    return;
  }
  if(colour == 'C'){
    strcpy(RGBcolour,"0 1 1"); 
    return;
  }
  if(colour == 'W'){
    strcpy(RGBcolour,"0.8 0.8 0.8 ");
    return;
  }
  strcpy(RGBcolour,"1 1 1 ");

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
        FWD_Interp(file);
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"3 Error");
  return false;
}

void FWD_Interp(script* file){
  int distance = 0;
  sscanf(file->wordArray[file->index],"%i",&distance);
  if(VAR(file)){
    int DollarSymbol = 0 ;
    if(file->wordArray[file->index][DollarSymbol] == '$'){
      strcpy(file->prevInstruction,"VAR");
      int LTRindex = 0;
      if(LTR(file, &LTRindex)){
        char letter = file->wordArray[file->index][1];
        int varArrayIndex = LTRToVarArrayIndex(letter);
        file->VARArray[varArrayIndex].VARType = NUMBER;         
        if(file->VARArray[varArrayIndex].VARType == NUMBER) {
          distance = file->VARArray[varArrayIndex].NUMBER;
        }
      }
    }
  }
  drawLine(file, distance);
  if(file->outputType != TTL){
    Output(file);
  }
}

bool RGT(script* file){
  bool RGT = strcmp(file->wordArray[file->index],"RIGHT");
  if(RGT == 0){
    file->index++;
    if(file->index < file->maxLen){
      if(VARNUM(file)){ 
        RGT_Interp(file);
        return true;
      }
    }
  }
  strcpy(file->errorMessage,"4 Error");
  return false;
}

void RGT_Interp(script* file){
  int degrees = 0;
  sscanf(file->wordArray[file->index],"%i",&degrees);
  file->turtle_Degrees += degrees;
  if(degrees > THREESIXTY){   
    degrees -= THREESIXTY;
    file->turtle_Degrees = degrees;
  }  
  if(VAR(file)){
    int DollarSymbol = 0 ;
    if(file->wordArray[file->index][DollarSymbol] == '$'){
      strcpy(file->prevInstruction,"VAR");
      int LTRindex = 0;
      if(LTR(file, &LTRindex)){
        char letter = file->wordArray[file->index][1];
        int varArrayIndex = LTRToVarArrayIndex(letter);
        file->VARArray[varArrayIndex].VARType = NUMBER; 
        if(file->VARArray[varArrayIndex].VARType == NUMBER) {
          file->turtle_Degrees = file->VARArray[varArrayIndex].NUMBER;
        }
      }
    }
  }
  if(file->outputType != TTL){
    Output(file);
  }
}

bool COL(script* file){
  bool COL = strcmp(file->wordArray[file->index],"COLOUR");
  if(COL != 0){
    strcpy(file->errorMessage,"5 Error");
    return false;
  }
  char errorMessage[ERRORMESSAGELENGTH] = "5 Error";
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }
  if(VAR(file)){
    COL_Interp_Vars(file);
    return true;
  }
  if(WORD(file)){ 
    COL_Interp(file);
    return true;
  }
  strcpy(file->errorMessage,"5 Error");
  return false;
}

void COL_Interp_Vars(script* file){
  char letter = file->wordArray[file->index][1];  
  int IndexVarArray = LTRToVarArrayIndex(letter);
  char colour[TOKENMAXLEN];
  strcpy(colour,file->VARArray[IndexVarArray].WORDCOLOUR); 
  file->turtle_Colour = colourToChar(colour);
}

void COL_Interp(script* file){
  file->turtle_Colour = colourToChar(file->wordArray[file->index]);
}

char colourToChar(char colour[TOKENMAXLEN]){
  if(strcmp(colour,"\"BLACK\"") == 0){
    return 'K';
  }
  if(strcmp(colour,"\"RED\"") == 0){
    return 'R';
  }
  if(strcmp(colour,"\"GREEN\"") == 0){
    return 'G';
  }
  if(strcmp(colour,"\"BLUE\"") == 0){
    return 'B';
  }
  if(strcmp(colour,"\"YELLOW\"") == 0){
    return 'Y';
  }
  if(strcmp(colour,"\"CYAN\"") == 0){
    return 'C';
  }
  if(strcmp(colour,"\"MAGENTA\"") == 0){
    return 'M';
  }
  if(strcmp(colour,"\"WHITE\"") == 0){
    return 'W';
  }
  return 'E';
}

bool LOOP(script* file){
  bool LOOP = strcmp(file->wordArray[file->index],"LOOP");
  if(LOOP != 0){
    strcpy(file->errorMessage,"6 Error");
    return false;
  }
  char errorMessage[ERRORMESSAGELENGTH] = "6 Error";
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }
  int LTRindex = 0;
  if(!LTR(file, &LTRindex)){ 
    strcpy(file->errorMessage,errorMessage);
    return false;  
  }  
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }  
  bool OVER = strcmp(file->wordArray[file->index],"OVER");
  if(!OVER == 0){
    strcpy(file->errorMessage,errorMessage);
    return false;
  }          
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }   
  int endCurlyBrace = endElement(file);
  int LSTindex = 0;
  if(!LST(file, &LSTindex)){ 
    strcpy(file->errorMessage,errorMessage);
    return false;
  }
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }  
  int IndexVarArray = LTRToVarArrayIndex(file->wordArray[LTRindex][0]);
  for(int loopCnt = LSTindex+1; loopCnt < endCurlyBrace; ++loopCnt){  
    wordOrNum(file, loopCnt, IndexVarArray);
    file->index = endCurlyBrace+1;
    if(!INSLST(file)){    
      strcpy(file->errorMessage,errorMessage);
      return false;
    }  
  }
  if(LSTindex+1 == endCurlyBrace){
    while(strcmp(file->wordArray[file->index],"END") != 0){
      file->index++;
    }
  }
  if(INSLST(file)){
    return true;
  }
  strcpy(file->errorMessage,errorMessage);
  return false;
}

void wordOrNum(script* file, int loopCounter, int IndexVarArray){ 
  if(isVARCOLOUR(file, loopCounter)){
    isWORD(file, loopCounter, IndexVarArray);
  }
  if(isValidNUM(file,loopCounter)){
    isNUM(file, loopCounter, IndexVarArray);
  }
}

void isWORD(script* file, int loopCounter, int IndexVarArray){ 
  file->VARArray[IndexVarArray].VARType = WORDCOLOUR;
  strcpy(file->VARArray[IndexVarArray].WORDCOLOUR, file->wordArray[loopCounter]);
}

bool isValidNUM(script *file, int index){
  double num = 0;
  char extraChar = '\0';
  int numItems = sscanf(file->wordArray[index],"%lf%c",&num, &extraChar);
  if(numItems == 1 && extraChar == '\0'){
    return true;
  }
  return false;
}

void isNUM(script* file, int loopCounter, int IndexVarArray){
  file->VARArray[IndexVarArray].VARType = NUMBER;
  double num = 0;
  char extraChar = '\0';
  int numItems = sscanf(file->wordArray[loopCounter],"%lf%c",&num, &extraChar);
  if(numItems == 1 && extraChar == '\0'){
    file->VARArray[IndexVarArray].NUMBER = (int)num;
  }
}

int endElement(script* file){
  int i = file->index;
  while(strcmp(file->wordArray[i],"}")!=0){  
    i++;
  }
  return i;
}

bool MaxIndexGraterThanIndex(script* file, char errorMessage[ERRORMESSAGELENGTH]){
  if(file->index >= file->maxLen){
    strcpy(file->errorMessage,errorMessage);
    return true;
  }
  return false;
}

int indexStartLoop(script* file){
  for(int i = file->index; ; i--){
    if(strcmp(file->wordArray[i],"LOOP") == 0){
      return i;
    }
  }
  return -1;
}

bool SET(script* file){
  bool SET = strcmp(file->wordArray[file->index],"SET");
  if(SET != 0){
    strcpy(file->errorMessage,"7 Error");
    return false;
  }
  char errorMessage[ERRORMESSAGELENGTH] = "7 Error";
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }   
  int LTRindex = 0;
  if(!LTR(file,&LTRindex)){
    strcpy(file->errorMessage,"7 Error");
    return false;
  }
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }     
  bool leftBracket = strcmp(file->wordArray[file->index],"(");
  if(leftBracket != 0){
    strcpy(file->errorMessage,errorMessage);
    return false;
  }
  int indexLTR = file->index-1;
  file->index++;
  if(MaxIndexGraterThanIndex(file,errorMessage)){
    return false;
  }     
  if(!PFIX(file, indexLTR)){
  strcpy(file->errorMessage,errorMessage);
  return false;
  }
  return true;
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
    int LTRindex = file->index;
    if(LTR(file,&LTRindex)){
      return true;
    }
  }
  strcpy(file->errorMessage,"9 Error");
  return false;
}

void init_VARArray(script* file){
  for(int i = 0; i < LENVARABLES; i++){
    file->VARArray[i].VARType = NONE;
  }
}

int LTRToVarArrayIndex(char LTRCharacter){
  int index = LTRCharacter - (int)'A';
  return index;
}

bool LTR(script* file, int* LTRindex){  
  *LTRindex = file->index;
  int lenght = strlen(file->wordArray[file->index]);
  if(!strcmp(file->prevInstruction,"VAR") && lenght == LENGTH){
    char Dollar[TOKENMAXLEN] = {'\0'};
    char noDollar[TOKENMAXLEN] = {'\0'};
    sscanf(file->wordArray[file->index],"%c%c",Dollar,noDollar);    
    int LTRLenPrev = strlen(noDollar);
    int LTRUpperPrev = isupper(noDollar[LTRLenPrev-1]);
  
  
    if(LTRLenPrev == 1 && LTRUpperPrev > 0){
      if(file->VARArray[LTRToVarArrayIndex(noDollar[0])].VARType == NONE){
        strcpy(file->errorMessage,"10 Error");
        return false;
      }
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

bool isVARCOLOUR(script* file, int index){
    if(strcmp(file->wordArray[index],"\"BLACK\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"RED\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"GREEN\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"BLUE\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"YELLOW\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"CYAN\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"MAGENTA\"") == 0){
      return true;
    }
    if(strcmp(file->wordArray[index],"\"WHITE\"") == 0){
      return true;
    }
  return false;
}

bool LST(script* file, int* leftBracePointer){
  bool leftBrace = strcmp(file->wordArray[file->index],"{");
  if(leftBrace == 0){
    *leftBracePointer = file->index; 
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

bool PFIX(script* file, int indexLTR){
  bool rightBracket = strcmp(file->wordArray[file->index],")");
  if(rightBracket == 0){
    setVAR(file,indexLTR);
    return true;
  }
  if(OP(file)){
    file->index++;
    if(file->index < file->maxLen){
      if(PFIX(file,indexLTR)){
        return true;
      }
    }  
  }
  if(VARNUM(file)){
    pushStr(file,file->wordArray[file->index]);
    file->index++;
    if(file->index < file->maxLen){
      if(PFIX(file,indexLTR)){
        return true;
      }
    }  
  }
  strcpy(file->errorMessage,"16 Error");
  return false;
}

bool OP(script* file){
  bool plus = strcmp(file->wordArray[file->index],"+");
  if(plus == 0){
    evaluatePostfix(file,PLUS);
    return true;
  }
  bool minus = strcmp(file->wordArray[file->index],"-");
  if(minus == 0){
    evaluatePostfix(file,MINUS);
    return true;
  }
  bool divide = strcmp(file->wordArray[file->index],"/");
  if(divide == 0){
    evaluatePostfix(file,DIVIDE);
    return true;
  }
  bool times = strcmp(file->wordArray[file->index],"*");
  if(times == 0){
    evaluatePostfix(file,TIMES);
    return true;
  }
  strcpy(file->errorMessage,"17 Error");
  return false;
}

void evaluatePostfix(script* file, int symbol){
  double val1 = pop(file);
  double val2 = pop(file);
  double result;
  switch (symbol) {
      case PLUS: 
        result = val2 + val1;
        push(file, result); 
        break;
      case MINUS: 
        result = val2 - val1;
        push(file, result); 
        break;
      case TIMES: 
        result = val2 * val1;
        push(file, result); 
        break;
      case DIVIDE: 
        result = val2 / val1;
        push(file, result); 
        break;
  }
}

void pushStr(script* prog, char pushValue[TOKENMAXLEN]){ 
  if(prog->stack.indexStack < prog->stack.maxLen ){
    double number;
    if(pushValue[0] == '$'){
      int indexVarArray = LTRToVarArrayIndex(pushValue[1]);
      if(prog->VARArray[indexVarArray].VARType == NUMBER){
        number = (double)prog->VARArray[indexVarArray].NUMBER;
        prog->stack.stackArray[prog->stack.indexStack] =  number;
        prog->stack.indexStack++;
        return;
      }
    }
    if(sscanf(pushValue,"%lf",&number)==1){
      prog->stack.stackArray[prog->stack.indexStack] = number;
      prog->stack.indexStack++;
      return;
    }
    return;
  }
  fprintf(stderr, "Stack size exceeded\n");
  return;
}

void push(script* prog, double number){
  if(prog->stack.indexStack < prog->stack.maxLen ){
    prog->stack.stackArray[prog->stack.indexStack] = number;
    prog->stack.indexStack++;
    return;
  }
  fprintf(stderr, "Stack size exceeded\n");
  return;
}

double pop(script* prog){
  double number;
  if(prog->stack.indexStack >= 1){
    prog->stack.indexStack--;
  }
  number = prog->stack.stackArray[prog->stack.indexStack];
  return number;  
}

void setVAR(script* prog, int indexLTR){
  char var = prog->wordArray[indexLTR][0];
  int indexVarArray = LTRToVarArrayIndex(var);
  long double value = pop(prog);
  prog->VARArray[indexVarArray].VARType = NUMBER;
  prog->VARArray[indexVarArray].NUMBER = value; 
  resetStack(prog);
  return;
}

void resetStack(script* prog){
  for(int i = 0; i < prog->stack.maxLen; i++){
    prog->stack.stackArray[i] = 0;
  }
  return;
}

