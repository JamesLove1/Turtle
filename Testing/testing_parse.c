#include"./parse.h"

void test(void){

  script* testInitTokenArray = init_script();
  init_wordArray(testInitTokenArray);
  assert(testInitTokenArray->wordArray != NULL);
  assert(testInitTokenArray->wordArray[0] != NULL);
  freeWordArray(testInitTokenArray);
  free_script(testInitTokenArray);

  script* testAddWord = init_script();
  init_wordArray(testAddWord);
  strcpy(testAddWord->wordArray[0],"wordOne");
  assert(strcmp(testAddWord->wordArray[0],"wordOne")==0);
  addWord(testAddWord);
  strcpy(testAddWord->wordArray[1],"wordTwo");
  assert(strcmp(testAddWord->wordArray[1],"wordTwo")==0);
  addWord(testAddWord);
  strcpy(testAddWord->wordArray[1],"wordThree");
  assert(strcmp(testAddWord->wordArray[1],"wordThree")==0);
  freeWordArray(testAddWord);
  free_script(testAddWord);

  script* testPROG = init_script();
  init_wordArray(testPROG);
  testPROG->index = 0;
  strcpy(testPROG->wordArray[testPROG->index],"START");
  addWord(testPROG);
  testPROG->index = 1;
  strcpy(testPROG->wordArray[testPROG->index],"END");
  testPROG->index = 0;
  assert(PROG(testPROG) == 1);
  assert(strcmp(testPROG->errorMessage,"") == 0);
  freeWordArray(testPROG);
  free_script(testPROG);
  
  script* testPROG1 = init_script();
  init_wordArray(testPROG1);
  testPROG1->index = 0;
  strcpy(testPROG1->wordArray[testPROG1->index],"END");
  assert(PROG(testPROG1) == 0);
  assert(strcmp(testPROG1->errorMessage,"Error")!=0);
  freeWordArray(testPROG1);
  free_script(testPROG1);

  script* testINSLST = init_script();
  init_wordArray(testINSLST);
  testINSLST->index = 0;
  strcpy(testINSLST->wordArray[testINSLST->index],"END");
  assert(INSLST(testINSLST)==1);
  freeWordArray(testINSLST);
  free_script(testINSLST);

  script* testINSLST1 = init_script();
  init_wordArray(testINSLST1);
  testINSLST1->index = 0;
  strcpy(testINSLST1->wordArray[testINSLST1->index],"FORWARD");
  addWord(testINSLST1);
  testINSLST1->index = 1;
  strcpy(testINSLST1->wordArray[testINSLST1->index],"10");
  addWord(testINSLST1);
  testINSLST1->index = 0;
  assert(INSLST(testINSLST1)==0);
  freeWordArray(testINSLST1);
  free_script(testINSLST1);

  script* testINSLST2 = init_script();
  init_wordArray(testINSLST2);
  testINSLST2->index = 0;
  strcpy(testINSLST2->wordArray[testINSLST2->index],"FORWARD");
  addWord(testINSLST2);
  testINSLST2->index = 1;
  strcpy(testINSLST2->wordArray[testINSLST2->index],"10");
  addWord(testINSLST2);
  testINSLST2->index = 2;
  strcpy(testINSLST2->wordArray[testINSLST2->index],"END");
  addWord(testINSLST2);
  testINSLST2->index = 0;
  assert(INSLST(testINSLST2)==1);
  freeWordArray(testINSLST2);
  free_script(testINSLST2);

  script* testINS = init_script();
  init_wordArray(testINS);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"FORWARD");
  addWord(testINS);
  testINS->index = 1;
  strcpy(testINS->wordArray[testINS->index],"1000");
  addWord(testINS);
  testINS->index = 0;
  assert(INS(testINS)==1);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"RIGHT");
  addWord(testINS);
  assert(INS(testINS)==1);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"END");
  addWord(testINS);
  assert(INS(testINS)==0);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"COLOUR");
  testINS->index = 1;
  strcpy(testINS->wordArray[testINS->index],"\"BLACK\"");
  testINS->index = 0;
  assert(INS(testINS)==1);
  testINS->index = 1;
  strcpy(testINS->wordArray[testINS->index],"$A");
  testINS->index = 0;
  assert(INS(testINS)==1);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"LOOP");
  testINS->index = 1;
  strcpy(testINS->wordArray[testINS->index],"A");
  addWord(testINS);
  testINS->index = 2;
  strcpy(testINS->wordArray[testINS->index],"OVER");
  addWord(testINS);
  testINS->index = 3;
  strcpy(testINS->wordArray[testINS->index],"{");
  addWord(testINS);
  testINS->index = 4;
  strcpy(testINS->wordArray[testINS->index],"\"BLACK\"");
  addWord(testINS);
  testINS->index = 5;
  strcpy(testINS->wordArray[testINS->index],"}");
  addWord(testINS);
  testINS->index = 6;
  strcpy(testINS->wordArray[testINS->index],"END");
  testINS->index = 0;
  assert(INS(testINS)==1);
  testINS->index = 0;
  strcpy(testINS->wordArray[testINS->index],"SET");  
  testINS->index = 1;
  strcpy(testINS->wordArray[testINS->index],"A");
  testINS->index = 2;
  strcpy(testINS->wordArray[testINS->index],"(");
  testINS->index = 3;
  strcpy(testINS->wordArray[testINS->index],"1");
  testINS->index = 4;
  strcpy(testINS->wordArray[testINS->index],"+");
  testINS->index = 5;
  strcpy(testINS->wordArray[testINS->index],"1");
  testINS->index = 5;
  strcpy(testINS->wordArray[testINS->index],")");
  testINS->index = 0;
  assert(INS(testINS)==1);
  freeWordArray(testINS);
  free_script(testINS);

  script* testFWD = init_script();
  init_wordArray(testFWD);
  testFWD->index = 0;
  strcpy(testFWD->wordArray[testFWD->index],"FORWARD");
  addWord(testFWD);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"10");
  addWord(testFWD);
  testFWD->index = 0;
  assert(FWD(testFWD)==1); 
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"1");
  testFWD->index = 0;
  assert(FWD(testFWD)==1); 
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"-10");
  testFWD->index = 0;
  assert(FWD(testFWD)==1);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"-1");
  testFWD->index = 0;
  assert(FWD(testFWD)==1);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"$A");
  testFWD->index = 0;
  assert(FWD(testFWD)==1); 
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"$B");
  testFWD->index = 0;
  assert(FWD(testFWD)==1); 
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"$AA");
  testFWD->index = 0;
  assert(FWD(testFWD)==0); 
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"$a");
  testFWD->index = 0;
  assert(FWD(testFWD)==0);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"A");
  testFWD->index = 0;
  assert(FWD(testFWD)==0);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"a");
  testFWD->index = 0;
  assert(FWD(testFWD)==0);
  testFWD->index = 1;
  strcpy(testFWD->wordArray[testFWD->index],"$1");
  testFWD->index = 0;
  assert(FWD(testFWD)==0);
  strcpy(testFWD->wordArray[testFWD->index],"RIGHT");
  addWord(testFWD);
  assert(FWD(testFWD)==0);
  strcpy(testFWD->wordArray[testFWD->index],"END");
  addWord(testFWD);
  assert(FWD(testFWD)==0);
  freeWordArray(testFWD);
  free_script(testFWD);

  script* testRGT = init_script();
  init_wordArray(testRGT);
  testRGT->index = 0;
  strcpy(testRGT->wordArray[testRGT->index],"RIGHT");
  addWord(testRGT);
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"10");
  addWord(testRGT);
  testRGT->index = 0;
  assert(RGT(testRGT)==1); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"1");
  testRGT->index = 0;
  assert(RGT(testRGT)==1); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"$A");
  testRGT->index = 0;
  assert(RGT(testRGT)==1); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"$AA");
  testRGT->index = 0;
  assert(RGT(testRGT)==0); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"$a");
  testRGT->index = 0;
  assert(RGT(testRGT)==0); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"a");
  testRGT->index = 0;
  assert(RGT(testRGT)==0); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"A");
  testRGT->index = 0;
  assert(RGT(testRGT)==0); 
  testRGT->index = 1;
  strcpy(testRGT->wordArray[testRGT->index],"$1");
  testRGT->index = 0;
  assert(RGT(testRGT)==0); 
  strcpy(testRGT->wordArray[testRGT->index],"LEFT");
  addWord(testRGT);
  assert(RGT(testRGT)==0);
  strcpy(testRGT->wordArray[testRGT->index],"END");
  addWord(testRGT);
  assert(RGT(testRGT)==0);
  freeWordArray(testRGT);
  free_script(testRGT);

  script* testCOL = init_script();
  init_wordArray(testCOL);
  testCOL->index = 0;
  strcpy(testCOL->wordArray[testCOL->index],"COLOUR");
  addWord(testCOL);
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"$A");
  addWord(testCOL);
  testCOL->index = 0;
  assert(COL(testCOL)==1); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"\"RED\"");
  testCOL->index = 0;
  assert(COL(testCOL)==1);   
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"\"BLACK\"");
  testCOL->index = 0;
  assert(COL(testCOL)==1); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"$B");
  testCOL->index = 0;
  assert(COL(testCOL)==1); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"$AA");
  testCOL->index = 0;
  assert(COL(testCOL)==0); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"$a");
  testCOL->index = 0;
  assert(COL(testCOL)==0); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"a");
  testCOL->index = 0;
  assert(COL(testCOL)==0); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"A");
  testCOL->index = 0;
  assert(COL(testCOL)==0); 
  testCOL->index = 1;
  strcpy(testCOL->wordArray[testCOL->index],"$1");
  testCOL->index = 0;
  assert(COL(testCOL)==0); 
  strcpy(testCOL->wordArray[testCOL->index],"LEFT");
  addWord(testCOL);
  assert(COL(testCOL)==0);
  strcpy(testCOL->wordArray[testCOL->index],"END");
  addWord(testCOL);
  assert(COL(testCOL)==0);
  strcpy(testCOL->wordArray[testCOL->index],"red");
  addWord(testCOL);
  assert(COL(testCOL)==0);
  strcpy(testCOL->wordArray[testCOL->index],"red red");
  addWord(testCOL);
  assert(COL(testCOL)==0);
  strcpy(testCOL->wordArray[testCOL->index],"red red red");
  addWord(testCOL);
  assert(COL(testCOL)==0);
  freeWordArray(testCOL);
  free_script(testCOL);

  script* testLOOP = init_script();
  init_wordArray(testLOOP);
  strcpy(testLOOP->wordArray[testLOOP->index],"LOOP");
  addWord(testLOOP);
  testLOOP->index = 1;
  strcpy(testLOOP->wordArray[testLOOP->index],"A");
  addWord(testLOOP);
  testLOOP->index = 2;
  strcpy(testLOOP->wordArray[testLOOP->index],"OVER");
  addWord(testLOOP);
  testLOOP->index = 3;
  strcpy(testLOOP->wordArray[testLOOP->index],"{");
  addWord(testLOOP);
  testLOOP->index = 4;
  strcpy(testLOOP->wordArray[testLOOP->index],"\"RED\"");
  addWord(testLOOP);
  testLOOP->index = 5;
  strcpy(testLOOP->wordArray[testLOOP->index],"}");
  addWord(testLOOP);
  testLOOP->index = 6;
  strcpy(testLOOP->wordArray[testLOOP->index],"END");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==1); 
  testLOOP->index = 0;
  strcpy(testLOOP->wordArray[testLOOP->index],"SET");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 0;
  strcpy(testLOOP->wordArray[testLOOP->index],"LOOP");
  testLOOP->index = 1;
  strcpy(testLOOP->wordArray[testLOOP->index],"$A");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 1;
  strcpy(testLOOP->wordArray[testLOOP->index],"A");
  testLOOP->index = 2;
  strcpy(testLOOP->wordArray[testLOOP->index],"TEST");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 2;
  strcpy(testLOOP->wordArray[testLOOP->index],"OVER");
  testLOOP->index = 3;
  strcpy(testLOOP->wordArray[testLOOP->index],"}");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 3;
  strcpy(testLOOP->wordArray[testLOOP->index],"{");
  testLOOP->index = 4;
  strcpy(testLOOP->wordArray[testLOOP->index],"red red");
  testLOOP->index = 0;
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 4;
  strcpy(testLOOP->wordArray[testLOOP->index],"RED");
  testLOOP->index = 5;
  strcpy(testLOOP->wordArray[testLOOP->index],"{");
  assert(LOOP(testLOOP)==0);
  testLOOP->index = 5;
  strcpy(testLOOP->wordArray[testLOOP->index],"}");
  freeWordArray(testLOOP);
  free_script(testLOOP);
 
  script* testSET = init_script();
  init_wordArray(testSET);
  strcpy(testSET->wordArray[testSET->index],"SET");
  addWord(testSET);
  testSET->index = 1;
  strcpy(testSET->wordArray[testSET->index],"A");
  addWord(testSET);
  testSET->index = 2;
  strcpy(testSET->wordArray[testSET->index],"(");
  addWord(testSET);
  testSET->index = 3;
  strcpy(testSET->wordArray[testSET->index],"1");
  addWord(testSET);
  testSET->index = 4;
  strcpy(testSET->wordArray[testSET->index],"+");
  addWord(testSET);
  testSET->index = 5;
  strcpy(testSET->wordArray[testSET->index],"1");
  addWord(testSET);
  testSET->index = 6;
  strcpy(testSET->wordArray[testSET->index],")");
  testSET->index = 0;
  assert(SET(testSET)==1);
  testSET->index = 0;
  strcpy(testSET->wordArray[testSET->index],"TEST");
  testSET->index = 0;
  assert(SET(testSET)==0);
  strcpy(testSET->wordArray[testSET->index],"SET");
  testSET->index = 1;
  strcpy(testSET->wordArray[testSET->index],"$A");
  testSET->index = 0;
  assert(SET(testSET)==0);
  testSET->index = 1;
  strcpy(testSET->wordArray[testSET->index],"A");
  testSET->index = 2;
  strcpy(testSET->wordArray[testSET->index],")");
  testSET->index = 0;
  assert(SET(testSET)==0);
  testSET->index = 2;
  strcpy(testSET->wordArray[testSET->index],"(");
  testSET->index = 3;
  strcpy(testSET->wordArray[testSET->index],"(");
  testSET->index = 0;
  assert(SET(testSET)==0);
  testSET->index = 3;
  strcpy(testSET->wordArray[testSET->index],"1");
  freeWordArray(testSET);
  free_script(testSET);

  script* testVARNUM = init_script();
  init_wordArray(testVARNUM);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"$A");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"0");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"1");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"5");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"-1");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"-10");
  assert(VARNUM(testVARNUM)==1);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"$AA");
  assert(VARNUM(testVARNUM)==0);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"$a");
  assert(VARNUM(testVARNUM)==0);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"$aa");
  assert(VARNUM(testVARNUM)==0);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"AA");
  assert(VARNUM(testVARNUM)==0);
  strcpy(testVARNUM->wordArray[testVARNUM->index],"aa");
  assert(VARNUM(testVARNUM)==0);
  freeWordArray(testVARNUM);
  free_script(testVARNUM);

  script* testVAR = init_script();
  init_wordArray(testVAR);
  testVAR->index = 0;
  strcpy(testVAR->wordArray[testVAR->index],"$A");
  assert(VAR(testVAR)==1);
  strcpy(testVAR->wordArray[testVAR->index],"$B");
  assert(VAR(testVAR)==1);
  strcpy(testVAR->wordArray[testVAR->index],"$C");
  assert(VAR(testVAR)==1);
  strcpy(testVAR->wordArray[testVAR->index],"$AA");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$BB");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$CC");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$a");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$b");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$c");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$aa");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$bb");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"$cc");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"a");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"aa");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"b");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"bb");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"c");
  assert(VAR(testVAR)==0);
  strcpy(testVAR->wordArray[testVAR->index],"cc");
  assert(VAR(testVAR)==0);
  freeWordArray(testVAR);
  free_script(testVAR);

  script* testLTR = init_script();
  init_wordArray(testLTR);
  strcpy(testLTR->wordArray[testLTR->index],"A");
  assert(LTR(testLTR)==1);
  strcpy(testLTR->wordArray[testLTR->index],"a");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->wordArray[testLTR->index],"aa");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->wordArray[testLTR->index],"AA");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->wordArray[testLTR->index],"B");
  assert(LTR(testLTR)==1);
  strcpy(testLTR->wordArray[testLTR->index],"b");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->wordArray[testLTR->index],"bb");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->wordArray[testLTR->index],"BB");
  assert(LTR(testLTR)==0);
  strcpy(testLTR->prevInstruction,"VAR");
  strcpy(testLTR->wordArray[testLTR->index],"$A");
  assert(LTR(testLTR)==1);
  assert(strcmp(testLTR->prevInstruction,"") == 0);
  strcpy(testLTR->prevInstruction,"VAR");
  strcpy(testLTR->wordArray[testLTR->index],"$B");
  assert(LTR(testLTR)==1);
  assert(strcmp(testLTR->prevInstruction,"") == 0);
  freeWordArray(testLTR);
  free_script(testLTR);

  script* testNUM = init_script();
  init_wordArray(testNUM);
  strcpy(testNUM->wordArray[testNUM->index],"10");
  addWord(testNUM);
  assert(NUM(testNUM)==1);
  strcpy(testNUM->wordArray[testNUM->index],"1");
  assert(NUM(testNUM)==1);
  strcpy(testNUM->wordArray[testNUM->index],"0");
  assert(NUM(testNUM)==1);
  strcpy(testNUM->wordArray[testNUM->index],"-1");
  assert(NUM(testNUM)==1);
  strcpy(testNUM->wordArray[testNUM->index],"START");
  assert(NUM(testNUM)==0);
  strcpy(testNUM->wordArray[testNUM->index],"END");
  assert(NUM(testNUM)==0);
  freeWordArray(testNUM);
  free_script(testNUM);

  script* testWORD = init_script();
  init_wordArray(testWORD);
  strcpy(testWORD->wordArray[testWORD->index],"\"BLACK\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"RED\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"GREEN\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"BLUE\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"YELLOW\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"CYAN\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"MAGENTA\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"WHITE\"");
  assert(WORD(testWORD)==1);
  strcpy(testWORD->wordArray[testWORD->index],"\"WHITE\" \"WHITE\"");
  assert(WORD(testWORD)==0);
  strcpy(testWORD->wordArray[testWORD->index],"\"white \" \"white\"");
  assert(WORD(testWORD)==0);
  strcpy(testWORD->wordArray[testWORD->index],"\"RED\" \"RED\" \"RED\"");
  assert(WORD(testWORD)==0);
  strcpy(testWORD->wordArray[testWORD->index],"\"red\" \"red\" \"red\"");
  assert(WORD(testWORD)==0);
  freeWordArray(testWORD);
  free_script(testWORD);

  script* testLST = init_script();
  init_wordArray(testLST);
  strcpy(testLST->wordArray[testLST->index],"{");
  addWord(testLST);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"\"RED\"");
  addWord(testLST);
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"}");
  testLST->index = 0;
  assert(LST(testLST)==1); 
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"1");
  testLST->index = 0;
  assert(LST(testLST)==1);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"-1");
  testLST->index = 0;
  assert(LST(testLST)==1);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$A");
  testLST->index = 0;
  assert(LST(testLST)==1);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$AA");
  testLST->index = 0;
  assert(LST(testLST)==0);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$a");
  testLST->index = 0;
  assert(LST(testLST)==0);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"\"BLACK\" \"BLACK\"");
  testLST->index = 0;
  assert(LST(testLST)==0);
  testLST->index = 0;
  strcpy(testLST->wordArray[testLST->index],"}");
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"\"BLACK\"");
  testLST->index = 0;
  assert(LST(testLST)==0);
  //mutiple ITEMS
  testLST->index = 0;
  strcpy(testLST->wordArray[testLST->index],"{");
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"\"RED\"");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"\"RED\"");
  addWord(testLST);
  testLST->index = 3;
  strcpy(testLST->wordArray[testLST->index],"}");
  testLST->index = 0;
  assert(LST(testLST)==1); 
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"10");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"10");
  testLST->index = 0;
  assert(LST(testLST)==1);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$A");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"$B");
  testLST->index = 0;
  assert(LST(testLST)==1);
  testLST->index = 0;
  strcpy(testLST->wordArray[testLST->index],"}");
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$A");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"$B");
  testLST->index = 0;
  assert(LST(testLST)==0);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"$AA");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"$A");
  testLST->index = 0;
  assert(LST(testLST)==0);
  testLST->index = 1;
  strcpy(testLST->wordArray[testLST->index],"\"BLACK\" \"BLACK\"");
  testLST->index = 2;
  strcpy(testLST->wordArray[testLST->index],"$A");
  testLST->index = 0;
  assert(LST(testLST)==0);
  freeWordArray(testLST);
  free_script(testLST);

  script* testITEMS = init_script();
  init_wordArray(testITEMS);
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==1);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"\"RED\"");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==1);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"$A");
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==1);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"1");
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==1);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"-1");
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==1);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"{");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"\"RED\" \"RED\"");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"\"RANDOM\"");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"\"red\" \"red\"");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"$AA");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"$a");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  testITEMS->index = 0;
  strcpy(testITEMS->wordArray[testITEMS->index],"$AA");
  addWord(testITEMS);
  testITEMS->index = 1;
  strcpy(testITEMS->wordArray[testITEMS->index],"}");
  testITEMS->index = 0;
  assert(ITEMS(testITEMS)==0);
  freeWordArray(testITEMS);
  free_script(testITEMS);

  script* testITEM = init_script();
  init_wordArray(testITEM);
  strcpy(testITEM->wordArray[testITEM->index],"$A");
  assert(ITEM(testITEM)==1);
  strcpy(testITEM->wordArray[testITEM->index],"1");
  assert(ITEM(testITEM)==1);
  strcpy(testITEM->wordArray[testITEM->index],"-1");
  assert(ITEM(testITEM)==1);
  strcpy(testITEM->wordArray[testITEM->index],"\"BLACK\"");
  assert(ITEM(testITEM)==1);
  strcpy(testITEM->wordArray[testITEM->index],"$AA");
  assert(ITEM(testITEM)==0);
  strcpy(testITEM->wordArray[testITEM->index],"$a");
  assert(ITEM(testITEM)==0);
  strcpy(testITEM->wordArray[testITEM->index],"$aa");
  assert(ITEM(testITEM)==0);
  strcpy(testITEM->wordArray[testITEM->index],"\"black\"");
  assert(ITEM(testITEM)==0);
  strcpy(testITEM->wordArray[testITEM->index],"\"BLACK\" \"BLACK\"");
  assert(ITEM(testITEM)==0);
  strcpy(testITEM->wordArray[testITEM->index],"\"black\" \"black\"");
  assert(ITEM(testITEM)==0);
  freeWordArray(testITEM);
  free_script(testITEM);

  script* testPFIX = init_script();
  init_wordArray(testPFIX);
  strcpy(testPFIX->wordArray[testPFIX->index],")");
  assert(PFIX(testPFIX)==1);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"+");
  testPFIX->index = 1;
  addWord(testPFIX);
  strcpy(testPFIX->wordArray[testPFIX->index],")");
  testPFIX->index = 0;
  assert(PFIX(testPFIX)==1);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"$A");
  assert(PFIX(testPFIX)==1);
  testPFIX->index = 1;
  strcpy(testPFIX->wordArray[testPFIX->index],"10");
  testPFIX->index = 2;
  addWord(testPFIX);
  strcpy(testPFIX->wordArray[testPFIX->index],"$B");
  testPFIX->index = 3;
  addWord(testPFIX);
  strcpy(testPFIX->wordArray[testPFIX->index],")");
  testPFIX->index = 0;
  assert(PFIX(testPFIX)==1);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"(");
  assert(PFIX(testPFIX)==0);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],")");
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"\\");
  assert(PFIX(testPFIX)==0);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"$a");
  assert(PFIX(testPFIX)==0);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"$AA");
  assert(PFIX(testPFIX)==0);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"a");
  assert(PFIX(testPFIX)==0);
  testPFIX->index = 0;
  strcpy(testPFIX->wordArray[testPFIX->index],"aa");
  assert(PFIX(testPFIX)==0);
  freeWordArray(testPFIX);
  free_script(testPFIX);

  script* testOP = init_script();
  init_wordArray(testOP);
  strcpy(testOP->wordArray[testOP->index],"=");
  assert(OP(testOP)==1);
  strcpy(testOP->wordArray[testOP->index],"+");
  assert(OP(testOP)==1);
  strcpy(testOP->wordArray[testOP->index],"-");
  assert(OP(testOP)==1);
  strcpy(testOP->wordArray[testOP->index],"/");
  assert(OP(testOP)==1);
  strcpy(testOP->wordArray[testOP->index],"*");
  assert(OP(testOP)==1);
  strcpy(testOP->wordArray[testOP->index],"x");
  assert(OP(testOP)==0);
  strcpy(testOP->wordArray[testOP->index],"+=");
  assert(OP(testOP)==0);
  freeWordArray(testOP);
  free_script(testOP);

}
