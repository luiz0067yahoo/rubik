#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN 0
#define BLUE 1
#define WHITE 2
#define YELLOW 3
#define ORANGE 4
#define RED 5

#define FRONT 0
#define BACK 1
#define UP 2
#define DOWN 3
#define RIGHT 4
#define LEFT 5

#define ORDERBYASC 'A'
#define ORDERBYDESC 'D'
#define COL 'L'
#define LINE 'C'

#define CUBECLEAR   'C'
#define CUBESAVE    'S'


char colors[6][7] ={"g", "b", "w", "y", "o", "r"};
char digits[10][2] ={"0","1","2","3","4","5","6","7","8","9"};
char moviments[18][3] ={"B","F","U","D","R","L","B'","F'","U'","D'","R'","L'","B2","F2","U2","D2","R2","L2"};
char reverseMoviments[18][3] ={"B'","F'","U'","D'","R'","L'","B","F","U","D","R","L","B2","F2","U2","D2","R2","L2"};

char *pieces [6][3][3];
char *piecesState [6][3][3];
char stateCube=CUBECLEAR;
char *piecesMove [3];

//############# STRING FUNCTIONS ########################

char *stringSubstring(char *str, int start, int end) {
    char *sub="";
    if(end!=0){
    int i, j;

    if(start >= end || end > strlen(str)) {
        return NULL;
    }

    sub = (char *) malloc(sizeof(char) * (end - start + 1));

    for(i = start, j = 0; i < end; i++, j++) {
        sub[j] = str[i];
    }

    sub[j] = '\0';
    }

    return sub;
}

int stringEquals(char *a,char *b){
    int size_a=strlen(a);
    int size_b=strlen(b);
    int count=-1;
    if(size_a==size_b){
        count=0;
        for(int i=0;i<size_a;i++){
            if(a[i]==b[i]){
               count++;
            }
        }
    }
    return count==size_a;
}

int stringIndexOf(char *text,char *word_){
	int T_text,T_word_;
	T_word_= strlen(word_);
	T_text = strlen(text);
	for (int i=0;i<T_text-T_word_;i++)
	{
		char *acc;
		acc=stringSubstring(text,i,i+T_word_);
		if(stringEquals(word_,acc)){
            break;
            return i;
		}
	}
	return -1;
}

int stringCount(char *text,char *word_){
	int T_text,T_word_,count;
	T_word_= strlen(word_);
	T_text = strlen(text);
	count=0;
	count=T_text;
	for (int i=0;i<T_text-T_word_;i++)
	{
		char *acc;
		acc=stringSubstring(text,i,i+T_word_);
		if(stringEquals(word_,acc)){
            count++;
		}
	}
	return count;
}

int stringCountChar(char *text,char word_){
	int T_text,count;
	T_text = strlen(text);
	count=0;
	for (int i=0;i<T_text-1;i++)
	{
		char acc=text[i];
		if(word_==acc){
            count++;
		}
	}
	return count;
}

char *stringLine(char *text,int line_number){
    char *line="";
    int T_text,count,start,end;
	T_text = strlen(text);
	count=0;
	start=0;
	end=T_text;
	for (int i=0;i<T_text-1;i++)
	{
		char acc=text[i];
		if('\n'==acc){
            if(count>=line_number){
                end=i;
                break;
            }
            else
                start=i+1;
            count++;
		}
	}
    line=stringSubstring(text,start,end);
    return line;
}

char *stringConcat(char *a,char *b){
    int size_a=strlen(a);
    int size_b=strlen(b);
    int size_total=size_a+size_b;
    char *str= malloc(size_total+1);
    for ( int i=0; i<size_a; i++ ){
        str[i]=a[i];
    }
    for ( int i=size_a; i<size_total; i++ ){
        str[i]=b[i-size_a];
    }
    str[size_total]='\0';
    return (str);
}

int stringCommandIndexOf(char *command){
    int i;
    int result=-1;
    for ( i = 0; i < 18; i++ ) {
        if(stringEquals(command,moviments[i])){
            result=i;
        }
    }
    return result;
}



//############# NUMBER FUNCTIONS ########################
int intArrayIndexOf(int find,int *IntArray,int size){
    int i;
    int result=-1;
    for ( i = 0; i < size; i++ ) {
        if(find==*(IntArray + i)){
            result=i;
        }
    }
    return result;
}

int stringArrayIndexOf(char *find,int *IntArray,int size){
    int i;
    int result=-1;
    for ( i = 0; i < size; i++ ) {
        if(stringEquals(find,(IntArray + i))){
            result=i;
        }
    }
    return result;
}

int *randomNumbersMax(int maxNumber,int qtdNumbers) {
    static int  *result;
    static int  numbers[100];
    *numbers=malloc(qtdNumbers);
    int i;
    int j;
    int acc;
    for ( i = 0; i < qtdNumbers; ++i) {
        while(1==1){
            acc = rand()%maxNumber;
            for (j = 0; j < i; ++j){
                if(acc==numbers[j]){
                    break;
                }
            }
            if(j==i){
                numbers[i]=acc;
                break;
            }
        }
        //printf( "*(p + %d) : %d\n", i, (numbers)[i]);
    }
    result=numbers;
    return result;
}

int mathAbs(int X){
    return ((X>=0)? X : -(X) );
}

int mathRound(float X){
    return  (X>=0)? (int) (X + 0.5) : (int)-(mathAbs(X) +0.5);
}



//############# commands ########################

char *extractCommand(char *command){
    char *ResultCommand="";
    char basicCommand[6]={'B','F','U','D','R','L'};
    char variantsCommand[3]={'\'','2','\n'};
    char line='\n';
    char acc1=(strlen(command)>0)?command[0]:' ';
    char acc2=(strlen(command)>1)?command[1]:' ';
    char acc3=(strlen(command)>2)?command[2]:' ';
    for ( int i=0; i< sizeof basicCommand; i++ ){
        if(basicCommand[i]==acc1){
            if (acc3==line){
                if(
                   (variantsCommand[0]==acc2)
                   ||
                   (variantsCommand[1]==acc2)
                   ||
                   (variantsCommand[2]==acc2)
                ){
                    ResultCommand=malloc(4);
                    ResultCommand[0]=acc1;
                    ResultCommand[1]=acc2;
                    ResultCommand[2]=line;
                    ResultCommand[3]='\0';
                }
                else{
                    ResultCommand=malloc(3);
                    ResultCommand[0]=acc1;
                    ResultCommand[1]=line;
                    ResultCommand[2]='\0';
                }
            }
            else{
                if(
                   (variantsCommand[0]==acc2)
                   ||
                   (variantsCommand[1]==acc2)
                   ||
                   (variantsCommand[2]==acc2)
                ){
                    ResultCommand=malloc(3);
                    ResultCommand[0]=acc1;
                    ResultCommand[1]=acc2;
                    ResultCommand[2]='\0';
                }
                else{
                    ResultCommand=malloc(2);
                    ResultCommand[0]=acc1;
                    ResultCommand[1]='\0';
                }
            }
        }
    }
    return ResultCommand;
}

char *clacCommands( char *command1, char *command2){
    char *result="";

    char *command1_line=(command1[strlen(command1)-1]=='\n')?"\n":"";
    char *command2_line=(command2[strlen(command2)-1]=='\n')?"\n":"";

    if((command2[0]==command1[0])&&(!command1_line[0]=='\n')){
        if(strlen(command1)==strlen(command2)){
            if(
                ((strlen(command2)==2)&&(command1[1]==command2[1])&&(command2[1]=='\''))
               ||
                (strlen(command2)==1)
            ){ //u'u' uu =2
                command2=malloc(3);
                command2[0]=command1[0];
                command2[1]='2';
                command2[2]='\0';
            }
            else if((strlen(command2)==2)&&(command1[1]==command2[1])&&(command2[1]=='2')){//u2u2
                command2="";
            }
            else{ //u2u' u'u2
                command2=malloc(2);
                command2[0]=command1[0];
                command2[1]='\0';
            }
        }
        else if(
                ((strlen(command2)==2)&&(command2[1]=='2'))
                ||
                ((strlen(command1)==2)&&(command1[1]=='2'))
                ){//u2u uu2  == u'

                command2=malloc(3);
                command2[0]=command1[0];
                command2[1]='\'';
                command2[2]='\0';
        }
         else if(
                ((strlen(command2)==2)&&(command2[1]=='\''))
                ||
                ((strlen(command1)==2)&&(command1[1]=='\''))
                ){//u'u uu'  ==
                command2="";
        }
        result=stringConcat(command2,command2_line);
    }
    else{
        //command2=stringConcat(command2,command2_line);
        //command1=stringConcat(command1,command1_line);
        result=stringConcat(command1,command2);
    }
    //result=stringConcat(command2,command2_line);
    //result=command1;
    return result;
}

char *createNewCommandChangeCurrencyCommand(char *commandPrior,char *commandCurrency, char *commandNext){
    char *newCommand=commandCurrency;
    char *commandCurrency_line=(commandCurrency[strlen(commandCurrency)-1]=='\n')?"\n":"";
    while(
          (commandPrior[0]==newCommand[0])
          ||
          (commandCurrency[0]==newCommand[0])
          ||
          (commandNext[0]==newCommand[0])
    ){
        newCommand=moviments[ rand() % 18];
   }
    newCommand=stringConcat(newCommand,commandCurrency_line);
    return newCommand;
}

char *crossCommandChangeCurrencyCommand(char *commandPrior,char *commandCurrency, char *commandNext,char *crossCommandPrior,char *crossCommandCurrency, char *crossCommandNext){
    char *newCommand=commandCurrency;
    char *commandCurrency_line=(commandCurrency[strlen(commandCurrency)-1]=='\n')?"\n":"";

    if(
       (crossCommandCurrency[0]!=commandCurrency[0])
       &&
       (crossCommandCurrency[0]!=commandPrior[0])
       &&
       (crossCommandCurrency[0]!=commandNext[0])
    )
        newCommand=crossCommandCurrency;
    else if (
       (crossCommandPrior[0]!=commandCurrency[0])
       &&
       (crossCommandPrior[0]!=commandPrior[0])
       &&
       (crossCommandPrior[0]!=commandNext[0])
    )
      newCommand=crossCommandPrior;
    else if (
       (crossCommandNext[0]!=commandCurrency[0])
       &&
       (crossCommandNext[0]!=commandPrior[0])
       &&
       (crossCommandNext[0]!=commandNext[0])
    )
      newCommand=crossCommandNext;
    char *newCommand_line=(newCommand[strlen(newCommand)-1]=='\n')?"\n":"";
    if((newCommand[strlen(newCommand)-1]!='\n')&&(commandCurrency_line[0]=='\n'))
        newCommand=stringConcat(newCommand,commandCurrency_line);
    else if((newCommand[strlen(newCommand)-1]=='\n')&&(commandCurrency_line[0]!='\n'))
        newCommand=stringSubstring(newCommand,0,strlen(newCommand)-2);
    return newCommand;
}

char *reverseCommand(char *tcommand){//delete duplicate commands calc commands equals face
  char *result="";
  int i=0;
  int commandsCount=0;
  int iscommand=0;
  char *commandCurrency="";
  while(i<strlen(tcommand)){
    commandCurrency=malloc(4);
    commandCurrency[0]=(strlen(tcommand)>i)?tcommand[i]:' ';
    commandCurrency[1]=(strlen(tcommand)>i+1)?tcommand[i+1]:' ';
    commandCurrency[2]=(strlen(tcommand)>i+2)?tcommand[i+2]:' ';;
    commandCurrency[3]='\0';
    commandCurrency=extractCommand(commandCurrency);
    iscommand=strlen(commandCurrency);
    if(iscommand>0){
        commandCurrency=reverseMoviments[stringArrayIndexOf(commandCurrency,moviments,18)];
        commandsCount++;
        result=stringConcat(commandCurrency,result);
    }
    i++;
  }

  return result;
}

char *trimCommand(char *tcommand){//delete duplicate commands calc commands equals face
  char *result="";
  int i=0;
  int commandsCount=0;
  int iscommand=0;
  char *commandCurrency="";
  char *commandPrior="";
  while(i<strlen(tcommand)){
    commandCurrency=malloc(4);
    commandCurrency[0]=(strlen(tcommand)>i)?tcommand[i]:' ';
    commandCurrency[1]=(strlen(tcommand)>i+1)?tcommand[i+1]:' ';
    commandCurrency[2]=(strlen(tcommand)>i+2)?tcommand[i+2]:' ';;
    commandCurrency[3]='\0';
    commandCurrency=extractCommand(commandCurrency);
    iscommand=strlen(commandCurrency);
    if(iscommand>0){
        commandsCount++;
        if(commandsCount%2==0){
            commandPrior=clacCommands(commandPrior,commandCurrency);
            result=stringConcat(result,commandPrior);
        }
        commandPrior=commandCurrency;
        i=i+iscommand;
    }
    else  i++;
  }
  if(commandsCount%2==1) result=stringConcat(result,commandPrior);
  if(!stringEquals(result,tcommand))
    result=trimCommand(result);
  return result;
}

void executeCommands(char *tcommand){
    int i=0;
    char *command="";
    if (strlen(tcommand)>0)
    for ( int i=0; i<strlen(tcommand); i++ )
    {
        command=malloc(3);
        command[0]=(strlen(tcommand)>i)?tcommand[i]:' ';
        command[1]=(strlen(tcommand)>i+1)?tcommand[i+1]:' ';
        command[2]='\0';
        command=extractCommand(command);

        CubeMove(command);
    }

}

//##################cube print############################################

void CubePrint(int *facesOrder){
    int face=facesOrder[0];
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            if (facesOrder[2]==LEFT)//rotate 90
                printf("%s",pieces[face][2-width][height]);
            else if (facesOrder[2]==RIGHT)//rotate 180
                printf("%s",pieces[face][width][2-height]);
            else if (facesOrder[2]==BACK)//rotate 180
                printf("%s",pieces[face][2-height][width]);
            else
            printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
    for ( int height=0; height<3; height++ ){
        face=facesOrder[1];
        for ( int width=0; width<3; width++ ){
            if (facesOrder[2]==UP)//rotate 90
                printf("%s",pieces[face][2-width][height]);
            else if (facesOrder[2]==BACK)//rotate 180
                printf("%s",pieces[face][height][2-width]);
            else if (facesOrder[2]==DOWN)//rotate 180
                printf("%s",pieces[face][width][2-height]);
            else
                printf("%s",pieces[face][height][width]);
        }
        face=facesOrder[2];
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        face=facesOrder[3];
        for ( int width=0; width<3; width++ ){
            if (facesOrder[2]==UP)//rotate -90
                printf("%s",pieces[face][width][2-height]);
            else if (facesOrder[2]==BACK)//rotate 180
                printf("%s",pieces[face][height][2-width]);
            else if (facesOrder[2]==DOWN)//rotate 180
                printf("%s",pieces[face][2-width][height]);
            else
                printf("%s",pieces[face][height][width]);
        }
        printf("\n");
    }
    face=facesOrder[4];
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            if (facesOrder[2]==LEFT)//rotate 90
                printf("%s",pieces[face][2-width][height]);
            else if (facesOrder[2]==RIGHT)//rotate 180
                printf("%s",pieces[face][width][2-height]);
            else if (facesOrder[2]==BACK)//rotate 180
                printf("%s",pieces[face][2-height][width]);
            else
                printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
    face=facesOrder[5];
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            //if (facesOrder[2]==GREEN)//rotate 90
                //printf("%s",pieces[face][height][width]);
                //printf("%s",pieces[face][2-height][width]);
            /*else if (facesOrder[2]==ORANGE)//rotate 180
                printf("%s",pieces[face][2-height][2-width]);
            */
            //else
                printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
}

void CubePrintFrontCenter(){
   int facesOrder[6]={UP,LEFT,FRONT,RIGHT,DOWN,BACK};
    CubePrint(facesOrder);
}

void CubePrintLeftCenter(){
   int facesOrder[6]={UP,BACK,LEFT,FRONT,DOWN,RIGHT};
    CubePrint(facesOrder);
}

void CubePrintRightCenter(){
   int facesOrder[6]={UP,FRONT,RIGHT,BACK,DOWN,LEFT};
   CubePrint(facesOrder);
}

void CubePrintUpCenter(){
   int facesOrder[6]={BACK,LEFT,UP,RIGHT,FRONT,DOWN};
   CubePrint(facesOrder);
}

void CubePrintBackCenter(){
   int facesOrder[6]={UP,RIGHT,BACK,LEFT,DOWN,FRONT};
   CubePrint(facesOrder);
}

void CubePrintDownCenter(){
   int facesOrder[6]={FRONT,LEFT,DOWN,RIGHT,BACK,UP};
   CubePrint(facesOrder);
}

//##################cube memory############################################
char *generateNameFace(int face,int height,int width){
    int pos=(3*height+width)+1;
    char *name=stringConcat(colors[face],digits[pos]);
    name=stringConcat(name," ");
    return name;
}

void CubeInitializer(){
     for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                pieces[face][height][width]=generateNameFace(face,height,width);
            }
        }
    }
}

void cubeLoadState(){
     for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                pieces[face][height][width]=piecesState[face][height][width];
            }
        }
    }
}

void cubeSaveState(){
     for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                piecesState[face][height][width]=pieces[face][height][width];
            }
        }
    }
}

void moveLineColFace(int faceOrigin,char typeColLineOrigin,int numberColLineOrigin, char order,int faceDest,char typeColLineDest,int numberColLineDest){
    if (order==ORDERBYASC){
        if ((typeColLineDest==LINE)&&(typeColLineOrigin==LINE))
            for ( int i=0; i<3; i++ ) pieces[faceDest][numberColLineDest][i]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if ((typeColLineDest==COL)&&(typeColLineOrigin==LINE))
            for ( int i=0; i<3; i++ ) pieces[faceDest][i][numberColLineDest]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if ((typeColLineDest==COL)&&(typeColLineOrigin==COL))
            for ( int i=0; i<3; i++ ) pieces[faceDest][i][numberColLineDest]=pieces[faceOrigin][i][numberColLineOrigin];//store line
        else if ((typeColLineDest==LINE)&&(typeColLineOrigin==COL))
            for ( int i=0; i<3; i++ ) pieces[faceDest][numberColLineDest][i]=pieces[faceOrigin][i][numberColLineOrigin];//store line
    }
    else if (order==ORDERBYDESC){
        if ((typeColLineDest==LINE)&&(typeColLineOrigin==LINE))
            for ( int i=0; i<3; i++ ) pieces[faceDest][numberColLineDest][2-i]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if ((typeColLineDest==COL)&&(typeColLineOrigin==LINE))
            for ( int i=0; i<3; i++ ) pieces[faceDest][2-i][numberColLineDest]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if ((typeColLineDest==COL)&&(typeColLineOrigin==COL))
            for ( int i=0; i<3; i++ ) pieces[faceDest][2-i][numberColLineDest]=pieces[faceOrigin][i][numberColLineOrigin];//store line
        else if ((typeColLineDest==LINE)&&(typeColLineOrigin==COL))
            for ( int i=0; i<3; i++ ) pieces[faceDest][numberColLineDest][2-i]=pieces[faceOrigin][i][numberColLineOrigin];//store line
    }
}

void saveLineColFace(int faceOrigin,char typeColLineOrigin,int numberColLineOrigin, char order){
    if (order==ORDERBYASC){
        if (typeColLineOrigin==LINE)
            for ( int i=0; i<3; i++ ) piecesMove[i]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if (typeColLineOrigin==COL)
            for ( int i=0; i<3; i++ ) piecesMove[i]=pieces[faceOrigin][i][numberColLineOrigin];//store line
    }
    else if (order==ORDERBYDESC){
        if (typeColLineOrigin==LINE)
            for ( int i=0; i<3; i++ ) piecesMove[2-i]=pieces[faceOrigin][numberColLineOrigin][i];//store line
        else if (typeColLineOrigin==COL)
            for ( int i=0; i<3; i++ ) piecesMove[2-i]=pieces[faceOrigin][i][numberColLineOrigin];//store line
    }
}

void loadLineColFace(int faceDest,char typeColLineDest,int numberColLineDest){
    if (typeColLineDest==LINE)
        for ( int i=0; i<3; i++ ) pieces[faceDest][numberColLineDest][i]= piecesMove[i];//store line
    else if (typeColLineDest==COL)
        for ( int i=0; i<3; i++ ) pieces[faceDest][i][numberColLineDest]= piecesMove[i];//store line
}

//##################cubemove############################################

void moveInternalFaceClockwise(int face){
    int height=0;
    int width=0;
    for ( int i=0; i<2; i++ ) piecesMove[i]=pieces[face][height][i+1];//store top face 2,3
    for ( int i=0; i<3; i++ ) pieces[face][height][2-i]=pieces[face][i][width];//move 1,4,7 to 1,2,3 position
    height=2;
    for ( int i=1; i<3; i++ ) pieces[face][i][width]=pieces[face][height][i];//move 8,9 to 4,7 position
    height=2;
    width=1;
    pieces[face][height][width]=pieces[face][height-1][width+1];//move 6 to 8 position
    width=2;
    for ( int i=0; i<2; i++ ) pieces[face][i+1][width]=piecesMove[i];//move 2,3 to 6,9 position
}

void moveInternalFaceCounterclockwise(int face){
    int height=0;
    int width=2;
    for ( int i=0; i<2; i++ ) piecesMove[i]=pieces[face][height][i];//store top face 1,2
    for ( int i=0; i<3; i++ ) pieces[face][height][i]=pieces[face][i][width];//move 3,6,9 to 1,2,3 position
    height=2;
    for ( int i=0; i<2; i++ ) pieces[face][i+1][width]=pieces[face][height][1-i];//move 7,8 to 6,9 position
    height=2;
    width=1;
    pieces[face][height][width]=pieces[face][height-1][width-1];//move 4 to 8 position
    width=0;
    for ( int i=0; i<2; i++ ) pieces[face][i+1][width]=piecesMove[1-i];//move 2,3 to 6,9 position*/
}

void moveRightClockwise(){
    moveInternalFaceClockwise(RIGHT);
    saveLineColFace(UP,COL,2,ORDERBYASC);
    moveLineColFace(FRONT,COL,2,ORDERBYDESC,UP,COL,2);
    moveLineColFace(DOWN,COL,2,ORDERBYASC,FRONT,COL,2);
    moveLineColFace(BACK,COL,2,ORDERBYDESC,DOWN,COL,2);
    loadLineColFace(BACK,COL,2);
}

void moveRightCounterclockwise(){
    moveInternalFaceCounterclockwise(RIGHT);
    saveLineColFace(UP,COL,2,ORDERBYDESC);
    moveLineColFace(BACK,COL,2,ORDERBYASC,UP,COL,2);
    moveLineColFace(DOWN,COL,2,ORDERBYDESC,BACK,COL,2);
    moveLineColFace(FRONT,COL,2,ORDERBYASC,DOWN,COL,2);
    loadLineColFace(FRONT,COL,2);
}

void moveLeftClockwise(){
    moveInternalFaceClockwise(LEFT);
    saveLineColFace(UP,COL,0,ORDERBYDESC);
    moveLineColFace(BACK,COL,0,ORDERBYASC,UP,COL,0);
    moveLineColFace(DOWN,COL,0,ORDERBYDESC,BACK,COL,0);
    moveLineColFace(FRONT,COL,0,ORDERBYASC,DOWN,COL,0);
    loadLineColFace(FRONT,COL,0);
}

void moveLeftCounterclockwise(){
    moveInternalFaceCounterclockwise(LEFT);
    saveLineColFace(UP,COL,0,ORDERBYASC);
    moveLineColFace(FRONT,COL,0,ORDERBYDESC,UP,COL,0);
    moveLineColFace(DOWN,COL,0,ORDERBYASC,FRONT,COL,0);
    moveLineColFace(BACK,COL,0,ORDERBYDESC,DOWN,COL,0);
    loadLineColFace(BACK,COL,0);
}

void moveUpClockwise(){
    moveInternalFaceClockwise(UP);
    saveLineColFace(FRONT,LINE,0,ORDERBYASC);
    moveLineColFace(RIGHT,LINE,0,ORDERBYASC,FRONT,LINE,0);
    moveLineColFace(BACK,LINE,2,ORDERBYDESC,RIGHT,LINE,0);
    moveLineColFace(LEFT,LINE,0,ORDERBYDESC,BACK,LINE,2);
    loadLineColFace(LEFT,LINE,0);
}

void moveUpCounterclockwise(){
    moveInternalFaceCounterclockwise(UP);
    saveLineColFace(FRONT,LINE,0,ORDERBYASC);
    moveLineColFace(LEFT,LINE,0,ORDERBYASC,FRONT,LINE,0);
    moveLineColFace(BACK,LINE,2,ORDERBYDESC,LEFT,LINE,0);
    moveLineColFace(RIGHT,LINE,0,ORDERBYDESC,BACK,LINE,2);
    loadLineColFace(RIGHT,LINE,0);
}

void moveDownClockwise(){
    moveInternalFaceClockwise(DOWN);
    saveLineColFace(FRONT,LINE,2,ORDERBYASC);
    moveLineColFace(LEFT,LINE,2,ORDERBYASC,FRONT,LINE,2);
    moveLineColFace(BACK,LINE,0,ORDERBYDESC,LEFT,LINE,2);
    moveLineColFace(RIGHT,LINE,2,ORDERBYDESC,BACK,LINE,0);
    loadLineColFace(RIGHT,LINE,2);
}

void moveDownCounterclockwise(){
    moveInternalFaceCounterclockwise(DOWN);
    saveLineColFace(FRONT,LINE,2,ORDERBYASC);
    moveLineColFace(RIGHT,LINE,2,ORDERBYASC,FRONT,LINE,2);
    moveLineColFace(BACK,LINE,0,ORDERBYDESC,RIGHT,LINE,2);
    moveLineColFace(LEFT,LINE,2,ORDERBYDESC,BACK,LINE,0);
    loadLineColFace(LEFT,LINE,2);
}

void moveFrontClockwise(){
    moveInternalFaceClockwise(FRONT);
    saveLineColFace(UP,LINE,2,ORDERBYASC);
    moveLineColFace(LEFT,COL,2,ORDERBYDESC,UP,LINE,2);
    moveLineColFace(DOWN,LINE,0,ORDERBYASC,LEFT,COL,2);
    moveLineColFace(RIGHT,COL,0,ORDERBYDESC,DOWN,LINE,0);
    loadLineColFace(RIGHT,COL,0);
}

void moveFrontCounterclockwise(){
    moveInternalFaceCounterclockwise(FRONT);
    saveLineColFace(UP,LINE,2,ORDERBYDESC);
    moveLineColFace(RIGHT,COL,0,ORDERBYASC,UP,LINE,2);
    moveLineColFace(DOWN,LINE,0,ORDERBYDESC,RIGHT,COL,0);
    moveLineColFace(LEFT,COL,2,ORDERBYASC,DOWN,LINE,0);
    loadLineColFace(LEFT,COL,2);
}

void moveBackClockwise(){
    moveInternalFaceClockwise(BACK);
    saveLineColFace(DOWN,LINE,2,ORDERBYDESC);
    moveLineColFace(LEFT,COL,0,ORDERBYASC,DOWN,LINE,2);
    moveLineColFace(UP,LINE,0,ORDERBYDESC,LEFT,COL,0);
    moveLineColFace(RIGHT,COL,2,ORDERBYASC,UP,LINE,0);
    loadLineColFace(RIGHT,COL,2);
}

void moveBackCounterclockwise(){
    moveInternalFaceCounterclockwise(BACK);
    saveLineColFace(DOWN,LINE,2,ORDERBYASC);
    moveLineColFace(RIGHT,COL,2,ORDERBYDESC,DOWN,LINE,2);
    moveLineColFace(UP,LINE,0,ORDERBYASC,RIGHT,COL,2);
    moveLineColFace(LEFT,COL,0,ORDERBYDESC,UP,LINE,0);
    loadLineColFace(LEFT,COL,0);
}

int CubeMove(char *str){
    if(strlen(str)==1){
        if(str[0]=='R'){
            moveRightClockwise();
        }
        else if(str[0]=='L'){
            moveLeftClockwise();
        }
        else if(str[0]=='U'){
            moveUpClockwise();
        }
        else if(str[0]=='D'){
            moveDownClockwise();
        }
        else if(str[0]=='F'){
            moveFrontClockwise();
        }
        else if(str[0]=='B'){
            moveBackClockwise();
        }
    }
    else if((strlen(str)==2)&&(str[1]=='\'')){
        if(str[0]=='R'){
            moveRightCounterclockwise();
        }
        else if(str[0]=='L'){
            moveLeftCounterclockwise();
        }
        else if(str[0]=='U'){
            moveUpCounterclockwise();
        }
        else if(str[0]=='D'){
            moveDownCounterclockwise();
        }
        else if(str[0]=='F'){
            moveFrontCounterclockwise();
        }
        else if(str[0]=='B'){
            moveBackCounterclockwise();
        }
    }
    else if((strlen(str)==2)&&(str[1]=='2')){
        for ( int i=0; i<2; i++ ){
            if(str[0]=='R'){
                moveRightClockwise();
            }
            else if(str[0]=='L'){
                moveLeftClockwise();
            }
            else if(str[0]=='U'){
                moveUpClockwise();
            }
            else if(str[0]=='D'){
                moveDownClockwise();
            }
            else if(str[0]=='F'){
                moveFrontClockwise();
            }
            else if(str[0]=='B'){
                moveBackClockwise();
            }
        }
    }
    return 0;
}



//####################################################################### GENETIC ALGORITIM ######################################################################################################

char *createCromossome(){//create cromossome
    ////srand( (unsigned)time(NULL) );
    return moviments[ rand() % 18];
}

char *createElement(int cromossomos){//element solution
    char *t_commands;
    char *newCommand="";
    char *lastCommand="";
    t_commands="";
    for (int i=0;i<cromossomos;i++){
        while(lastCommand[0]==newCommand[0]){
				newCommand=createCromossome();
        }
		lastCommand=newCommand;
        t_commands=stringConcat(t_commands,newCommand);
    }
    return t_commands;
}

char *generatePopulation(int limitLength,int chromosomesLength){//array elements separete by line
    char *population;
    for (int i=0;i<limitLength;i++){
        char *element;
        element=createElement(chromosomesLength);
        if(i==0){
            population=element;
        }
        else{
            population=stringConcat(population,"\n");
            population=stringConcat(population,element);
        }
    }
    return population;
}

char *invertPopulation(char *population){//reverse order population
    char *result=population;
    int count_line=stringCountChar(population,'\n');
    count_line++;
    for(int i=0;i<count_line;i++){
        char *element=stringLine(population,count_line-i-1);

        if(i==0)
            result=element;
        else{
            result=stringConcat(result,"\n");
            result=stringConcat(result,element);
        }
    }
    return result;
}

char *shufflePopulation(char *population){//randon order population
    char *result=population;
    int count_line=stringCountChar(population,'\n');
    count_line++;
    int *Numbers_=randomNumbersMax(count_line,count_line);

    for(int i=0;i<count_line;i++){
        char *element;
        element=stringLine(population,*(Numbers_+i));
        if(i==0)
            result=element;
        else{
            result=stringConcat(result,"\n");
            result=stringConcat(result,element);
        }
    }
    return result;
}

float cubeScoreCurrencyState(){//
	float count=0;
	for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                int pos=(3*height+width)+1;
                char *name;
                name=colors[face];
                if (stringEquals(pieces[face][height][width],generateNameFace(face,height,width)))
                {
                  count++;
                }
            }
        }
    }
	//6 pieces fixed center
	//54 all faces expost
	//54-6=48 faces moved
	count=(count-6);
	float result=(count==0)?0:count/48;
	return result;
}

float calcScore(char *commands,char *element){
    if(stateCube==CUBECLEAR){
        CubeInitializer();
        executeCommands(commands);
        cubeSaveState();
        executeCommands(element);
        stateCube=CUBESAVE;
    }
    else{
        cubeLoadState();
        executeCommands(element);
    }
    return cubeScoreCurrencyState();

}

int isPerfectCube(char *commands,char *population,int score){
    int count_line=stringCountChar(population,'\n');
    int scoreElement=0;
    char *element="";
    if  (count_line==0){//unique element in population
        element=stringLine(population,0);
        scoreElement=calcScore(commands,element);
    }
    return (int)((count_line==0)&&(scoreElement==score));
}

char *selectTournament(char * commands,char *population,int players,int score){
    char *crossPopulation=shufflePopulation(population);
    char *populationSelect="";
    int count_line=stringCountChar(crossPopulation,'\n');
    int j=0;
    while(j<count_line){
        int scoreBestElement=0;
        char *bestElement="";
        for(int i=0;((i<=players)&&(j+i<count_line));i++){
            char *element=stringLine(crossPopulation,j+i);
            int scoreElement=calcScore(commands,element);
            if(strlen(bestElement)==0){
                bestElement=element;
                scoreBestElement=scoreElement;
            }
            else if(scoreElement>scoreBestElement){
                    scoreBestElement=scoreElement;
                    bestElement=element;
            }
        }
        if(score==scoreBestElement)return bestElement;

        else{
            if(strlen(populationSelect)==0)
                populationSelect=bestElement;
            else{
                bestElement=stringConcat("\n",bestElement);
                populationSelect=stringConcat(populationSelect,bestElement);
            }
        }
        j=j+players;
    }
    return populationSelect;
}

char *crossOver(char *population,int qtdCrossOverIn100){
    char *crossPopulation=shufflePopulation(population);
    char *result="";
    int i=0;
    int *pointsChange;
    int maxNumber=100;
    pointsChange=randomNumbersMax( maxNumber, qtdCrossOverIn100);
    int activePoint=-1;
    int crossCommandsCount=0;
    int commandsCount=0;
    int isCrossCommand=0;
    int isCommand=0;
    char *crossCommand="";
    char *command="";
    char *commandPrior="";
    char *crossCommandPrior="";
    char *commandCurrency="";
    char *crossCommandCurrency="";
    char *newCommandCurrency="";
    char *commandNext="";
    char *crossCommandNext="";
    activePoint=intArrayIndexOf(commandsCount%100,pointsChange,qtdCrossOverIn100);
    while(i<strlen(population)){
        crossCommand=malloc(4);
        crossCommand[0]=(strlen(crossPopulation-1)>i)?crossPopulation[i]:' ';
        crossCommand[1]=(strlen(crossPopulation-1)>i+1)?crossPopulation[i+1]:' ';
        crossCommand[2]=(strlen(crossPopulation-1)>i+2)?crossPopulation[i+2]:' ';
        crossCommand[3]='\0';
        crossCommand=extractCommand(crossCommand);
        isCrossCommand=strlen(crossCommand);
        if(isCrossCommand>0){
            crossCommandsCount++;
            if(crossCommandsCount==1) crossCommandPrior=crossCommand;
            else if(crossCommandsCount==2) crossCommandCurrency=crossCommand;
            else if(crossCommandsCount>=3) crossCommandNext=crossCommand;
        }

        command=malloc(4);
        command[0]=(strlen(population-1)>i)?population[i]:' ';
        command[1]=(strlen(population-1)>i+1)?population[i+1]:' ';
        command[2]=(strlen(population-1)>i+2)?population[i+2]:' ';
        command[3]='\0';
        command=extractCommand(command);
        isCommand=strlen(command);
        if(isCommand>0){//command
            commandsCount++;
            if(commandsCount==1) commandPrior=command;
            else if(commandsCount==2){//start command
                commandCurrency=command;
                if(activePoint>-1) commandPrior=crossCommandChangeCurrencyCommand(commandPrior,commandPrior,commandCurrency,crossCommandPrior,crossCommandPrior,crossCommandCurrency);
                result=stringConcat(result,commandPrior);
            }
            else if(commandsCount>=3)
            {
                commandNext=command;
                newCommandCurrency=commandCurrency;
                if(activePoint>-1) newCommandCurrency=crossCommandChangeCurrencyCommand(commandPrior,commandCurrency,commandNext,crossCommandPrior,crossCommandCurrency,crossCommandNext);
                commandPrior=newCommandCurrency;
                commandCurrency=commandNext;
            }
            result=stringConcat(result,newCommandCurrency);
            if(((strlen(population-1)>i+1)&&(population[i+1]=='\0')) || ((strlen(population-1)>i+2)&&(population[i+2]=='\0'))){
                if(activePoint>-1)commandNext=crossCommandChangeCurrencyCommand(commandPrior,commandNext,commandNext,crossCommandPrior,crossCommandCurrency,crossCommandNext);
                result=stringConcat(result,commandNext);
            }
        }
        if((isCrossCommand)&&(crossCommandsCount>=3)){
            crossCommandPrior=crossCommandCurrency;
            crossCommandCurrency=crossCommandNext;
        }
        i++;
  }
  //return crossPopulation;
  return result;
}

char *mutation(char *population,int qtdMutacaoIn100){
    char *result="";
    int i=0;
    int *pointsChange;
    int maxNumber=100;
    pointsChange=randomNumbersMax( maxNumber, qtdMutacaoIn100);
    int activePoint=-1;
    int commandsCount=0;
    int iscommand=0;
    char *command="";
    char *commandPrior="";
    char *commandCurrency="";
    char *newCommandCurrency="";
    char *commandNext="";
    activePoint=intArrayIndexOf(commandsCount%100,pointsChange,qtdMutacaoIn100);
    while(i<strlen(population)){
        command=malloc(4);
        command[0]=(strlen(population-1)>i)?population[i]:' ';
        command[1]=(strlen(population-1)>i+1)?population[i+1]:' ';
        command[2]=(strlen(population-1)>i+2)?population[i+2]:' ';
        command[3]='\0';
        command=extractCommand(command);
        iscommand=strlen(command);
        if(iscommand>0){
            commandsCount++;
            if(commandsCount==1){
                commandPrior=command;
            }
            else if(commandsCount==2){//start command
                commandCurrency=command;
                if(activePoint>-1)
                    commandPrior=createNewCommandChangeCurrencyCommand(commandPrior,commandPrior,commandCurrency);
                result=stringConcat(result,commandPrior);
            }
            else if(commandsCount>=3)
            {
                commandNext=command;
                newCommandCurrency=commandCurrency;
                if(activePoint>-1)
                    newCommandCurrency=createNewCommandChangeCurrencyCommand(commandPrior,commandCurrency,commandNext);
                commandPrior=newCommandCurrency;
                commandCurrency=commandNext;
            }


            result=stringConcat(result,newCommandCurrency);

            if(//end
                    ((strlen(population-1)>i+1)&&(population[i+1]=='\0'))
                    ||
                    ((strlen(population-1)>i+2)&&(population[i+2]=='\0'))
            ){
                if(activePoint>-1)
                    commandNext=createNewCommandChangeCurrencyCommand(commandPrior,commandNext,commandNext);
                result=stringConcat(result,commandNext);
            }

        }
        i++;
  }
  return result;
}

char *formatResultSolver(char * commands,int startPopulation,int limitLength,int chromosomesLength,float playersTournament,int score,float percent_mutation,float percert_cross,int gerations){
    char *result="{";
    result=stringConcat(result,"\ncommands:\'");result=stringConcat(result,commands);result=stringConcat(result,"\'");
    result=stringConcat(result,"\n,startPopulation:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,limitLength:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,chromosomesLength:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,playersTournament:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,score:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,percent_mutation:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,percert_cross:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n,gerations:");result=stringConcat(result,commands);
    result=stringConcat(result,"\n}");
    return result;
}

char *solver(char * commands,int startPopulation,int limitLength,int chromosomesLength,float playersTournament,int score,float percent_mutation,float percert_cross,int gerations){
    stateCube=CUBECLEAR;
    char *population=generatePopulation(startPopulation,chromosomesLength) ;
    CubeInitializer();
    executeCommands(commands);
    cubeSaveState();
    for(int i=0;i<gerations;i++)
    {
        population=selectTournament(commands,population,playersTournament,score);
        if (isPerfectCube(commands,population,score)){ return population;}
        else{
            population=stringConcat(population,"\n");
            population=stringConcat(population,generatePopulation(limitLength,chromosomesLength));
        }
        population=mutation(population,percent_mutation);
        population=crossOver(population,percert_cross);
    }
    return population;
}


char* teste(){
    //char* commands="R";
    int i=6;
    //for(int i=0;i<18;i++)
    {
        char* commands=createElement(i);
        char* population="";
        char* result="";
        int startPopulation=150;
        int limitLength=100;
        int chromosomesLength=i;
        float playersTournament=2;
        float score=1;
        float percent_mutation=3;
        float percert_cross=3;
        int gerations=4000;
        population=solver(commands,startPopulation,limitLength,chromosomesLength,playersTournament,score,percent_mutation,percert_cross,gerations);
        if(isPerfectCube(commands,population,score)){
            result=population;
        }

    }
}

int main(){
    char *str="";
    teste();

    return 0;
}

/*
var wasmCode = new Uint8Array([0,97,115,109,1,0,0,0,1,185,128,128,128,0,5,96,1,127,1,127,96,3,127,127,127,1,127,96,2,127,127,1,127,96,30,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,1,127,96,0,1,127,2,168,128,128,128,0,3,3,101,110,118,6,109,97,108,108,111,99,0,0,3,101,110,118,6,109,101,109,99,112,121,0,1,3,101,110,118,6,115,116,114,108,101,110,0,0,3,138,128,128,128,0,9,1,2,2,3,0,0,0,4,4,4,132,128,128,128,0,1,112,0,0,5,131,128,128,128,0,1,0,1,6,129,128,128,128,0,0,7,161,129,128,128,0,10,6,109,101,109,111,114,121,2,0,15,115,116,114,105,110,103,83,117,98,115,116,114,105,110,103,0,3,12,115,116,114,105,110,103,67,111,110,99,97,116,0,4,12,115,116,114,105,110,103,69,113,117,97,108,115,0,5,21,97,114,114,97,121,78,117,109,98,101,114,115,84,111,67,111,109,109,97,110,100,0,6,20,115,116,114,105,110,103,67,111,109,109,97,110,100,73,110,100,101,120,79,102,0,7,14,101,120,116,114,97,99,116,67,111,109,109,97,110,100,0,8,14,114,101,118,101,114,115,101,67,111,109,109,97,110,100,0,9,12,116,101,115,116,101,114,101,118,101,114,115,101,0,10,4,109,97,105,110,0,11,10,178,177,128,128,0,9,203,128,128,128,0,1,1,127,2,64,32,2,69,13,0,65,0,33,3,2,64,32,2,32,1,76,13,0,32,0,16,2,32,2,73,13,0,65,1,32,1,107,32,2,106,16,0,34,3,32,0,32,1,106,32,2,32,1,107,34,2,16,1,32,2,106,65,0,58,0,0,11,32,3,15,11,65,144,1,11,223,128,128,128,0,1,4,127,32,0,16,2,34,2,32,1,16,2,34,3,106,34,4,65,1,106,16,0,33,5,2,64,32,2,65,1,72,13,0,32,5,32,0,32,2,16,1,26,11,2,64,32,3,65,1,72,13,0,32,5,32,2,106,32,1,32,4,32,2,65,1,106,34,0,32,4,32,0,74,27,32,2,107,16,1,26,11,32,5,32,4,106,65,0,58,0,0,32,5,11,214,128,128,128,0,1,3,127,65,127,33,4,2,64,32,0,16,2,34,2,32,1,16,2,71,13,0,65,0,33,4,32,2,65,1,72,13,0,32,2,33,3,3,64,32,4,32,0,45,0,0,32,1,45,0,0,70,106,33,4,32,1,65,1,106,33,1,32,0,65,1,106,33,0,32,3,65,127,106,34,3,13,0,11,11,32,4,32,2,70,11,199,155,128,128,0,1,4,127,65,144,1,33,33,2,64,32,0,65,18,72,13,0,32,0,65,3,108,65,16,106,34,32,16,2,34,0,65,1,106,16,0,33,33,2,64,32,0,65,1,72,13,0,32,33,32,32,32,0,16,1,26,11,32,33,32,0,106,65,0,58,0,0,11,2,64,2,64,32,1,65,18,72,13,0,32,33,16,2,34,0,32,1,65,3,108,65,16,106,34,30,16,2,34,31,106,34,32,65,1,106,16,0,33,1,2,64,32,0,65,1,72,13,0,32,1,32,33,32,0,16,1,26,11,2,64,32,31,65,1,72,13,0,32,1,32,0,106,32,30,32,32,32,0,65,1,106,34,33,32,32,32,33,74,27,32,0,107,16,1,26,11,32,1,32,32,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,2,65,18,72,13,0,32,1,16,2,34,0,32,2,65,3,108,65,16,106,34,31,16,2,34,32,106,34,2,65,1,106,16,0,33,33,2,64,32,0,65,1,72,13,0,32,33,32,1,32,0,16,1,26,11,2,64,32,32,65,1,72,13,0,32,33,32,0,106,32,31,32,2,32,0,65,1,106,34,1,32,2,32,1,74,27,32,0,107,16,1,26,11,32,33,32,2,106,65,0,58,0,0,32,3,65,18,78,13,1,12,2,11,32,1,33,33,32,3,65,18,72,13,1,11,32,33,16,2,34,2,32,3,65,3,108,65,16,106,34,32,16,2,34,3,106,34,0,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,3,65,1,72,13,0,32,1,32,2,106,32,32,32,0,32,2,65,1,106,34,33,32,0,32,33,74,27,32,2,107,16,1,26,11,32,1,32,0,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,4,65,18,72,13,0,32,1,16,2,34,2,32,4,65,3,108,65,16,106,34,3,16,2,34,0,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,0,65,1,72,13,0,32,33,32,2,106,32,3,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,5,65,18,78,13,1,12,2,11,32,1,33,33,32,5,65,18,72,13,1,11,32,33,16,2,34,2,32,5,65,3,108,65,16,106,34,3,16,2,34,0,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,0,65,1,72,13,0,32,1,32,2,106,32,3,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,6,65,18,72,13,0,32,1,16,2,34,2,32,6,65,3,108,65,16,106,34,0,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,0,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,7,65,18,78,13,1,12,2,11,32,1,33,33,32,7,65,18,72,13,1,11,32,33,16,2,34,2,32,7,65,3,108,65,16,106,34,0,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,0,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,8,65,18,72,13,0,32,1,16,2,34,2,32,8,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,9,65,18,78,13,1,12,2,11,32,1,33,33,32,9,65,18,72,13,1,11,32,33,16,2,34,2,32,9,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,10,65,18,72,13,0,32,1,16,2,34,2,32,10,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,11,65,18,78,13,1,12,2,11,32,1,33,33,32,11,65,18,72,13,1,11,32,33,16,2,34,2,32,11,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,12,65,18,72,13,0,32,1,16,2,34,2,32,12,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,13,65,18,78,13,1,12,2,11,32,1,33,33,32,13,65,18,72,13,1,11,32,33,16,2,34,2,32,13,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,14,65,18,72,13,0,32,1,16,2,34,2,32,14,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,15,65,18,78,13,1,12,2,11,32,1,33,33,32,15,65,18,72,13,1,11,32,33,16,2,34,2,32,15,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,16,65,18,72,13,0,32,1,16,2,34,2,32,16,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,17,65,18,78,13,1,12,2,11,32,1,33,33,32,17,65,18,72,13,1,11,32,33,16,2,34,2,32,17,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,18,65,18,72,13,0,32,1,16,2,34,2,32,18,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,19,65,18,78,13,1,12,2,11,32,1,33,33,32,19,65,18,72,13,1,11,32,33,16,2,34,2,32,19,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,20,65,18,72,13,0,32,1,16,2,34,2,32,20,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,21,65,18,78,13,1,12,2,11,32,1,33,33,32,21,65,18,72,13,1,11,32,33,16,2,34,2,32,21,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,22,65,18,72,13,0,32,1,16,2,34,2,32,22,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,23,65,18,78,13,1,12,2,11,32,1,33,33,32,23,65,18,72,13,1,11,32,33,16,2,34,2,32,23,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,24,65,18,72,13,0,32,1,16,2,34,2,32,24,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,25,65,18,78,13,1,12,2,11,32,1,33,33,32,25,65,18,72,13,1,11,32,33,16,2,34,2,32,25,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,2,64,32,26,65,18,72,13,0,32,1,16,2,34,2,32,26,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,27,65,18,78,13,1,12,2,11,32,1,33,33,32,27,65,18,72,13,1,11,32,33,16,2,34,2,32,27,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,1,2,64,32,2,65,1,72,13,0,32,1,32,33,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,1,32,2,106,32,8,32,4,32,2,65,1,106,34,33,32,4,32,33,74,27,32,2,107,16,1,26,11,32,1,32,4,106,65,0,58,0,0,12,1,11,32,33,33,1,11,2,64,2,64,2,64,32,28,65,18,72,13,0,32,1,16,2,34,2,32,28,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,33,2,64,32,2,65,1,72,13,0,32,33,32,1,32,2,16,1,26,11,2,64,32,6,65,1,72,13,0,32,33,32,2,106,32,8,32,4,32,2,65,1,106,34,1,32,4,32,1,74,27,32,2,107,16,1,26,11,32,33,32,4,106,65,0,58,0,0,32,29,65,18,78,13,1,12,2,11,32,1,33,33,32,29,65,18,72,13,1,11,32,33,16,2,34,1,32,29,65,3,108,65,16,106,34,8,16,2,34,6,106,34,4,65,1,106,16,0,33,2,2,64,32,1,65,1,72,13,0,32,2,32,33,32,1,16,1,26,11,2,64,32,6,65,1,72,13,0,32,2,32,1,106,32,8,32,4,32,1,65,1,106,34,33,32,4,32,33,74,27,32,1,107,16,1,26,11,32,2,32,4,106,65,0,58,0,0,32,2,15,11,32,33,11,219,131,128,128,0,1,8,127,2,64,32,0,16,2,34,1,65,1,72,13,0,65,0,33,3,65,16,33,2,65,127,33,8,3,64,65,127,33,7,2,64,32,1,32,3,65,3,108,65,16,106,16,2,71,13,0,65,0,33,7,32,0,33,4,32,2,33,5,32,1,33,6,3,64,32,7,32,4,45,0,0,32,5,45,0,0,70,106,33,7,32,4,65,1,106,33,4,32,5,65,1,106,33,5,32,6,65,127,106,34,6,13,0,11,11,32,3,32,8,32,7,32,1,70,27,33,8,32,2,65,3,106,33,2,32,3,65,1,106,34,3,65,18,71,13,0,11,32,8,15,11,65,17,65,16,65,15,65,14,65,13,65,12,65,11,65,10,65,9,65,8,65,7,65,6,65,5,65,4,65,3,65,2,65,1,65,127,65,0,32,1,65,127,65,0,32,1,65,16,16,2,71,27,71,27,32,1,65,127,65,0,32,1,65,19,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,22,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,25,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,28,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,31,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,34,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,37,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,40,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,43,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,46,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,49,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,52,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,55,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,58,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,61,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,192,0,16,2,71,27,70,27,32,1,65,127,65,0,32,1,65,195,0,16,2,71,27,70,27,11,184,141,128,128,0,1,2,127,32,0,45,0,0,33,2,65,32,33,1,2,64,32,0,16,2,65,2,73,13,0,32,0,45,0,1,33,1,11,32,2,65,32,32,2,27,33,2,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,2,64,32,0,16,2,65,2,77,13,0,32,0,45,0,2,65,10,71,13,1,32,1,65,255,1,113,65,50,71,13,3,32,2,65,194,0,71,13,4,65,4,16,0,34,0,65,194,228,40,54,0,0,32,0,15,11,32,1,65,255,1,113,65,50,71,13,1,12,42,11,32,1,65,255,1,113,65,50,70,13,41,11,65,144,1,33,0,32,2,65,190,127,106,34,2,65,19,75,13,41,2,64,32,2,14,20,0,42,4,42,5,42,42,42,42,42,6,42,42,42,42,42,7,42,42,8,0,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,11,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,194,0,58,0,0,32,0,65,2,106,33,1,12,11,11,32,2,65,194,0,71,13,1,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,8,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,194,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,8,11,65,144,1,33,0,32,2,65,188,127,106,34,1,65,17,75,13,39,2,64,32,1,14,18,0,40,21,40,40,40,40,40,22,40,40,40,40,40,23,40,40,24,0,11,65,4,16,0,34,0,65,196,228,40,54,0,0,32,0,15,11,65,144,1,33,0,32,2,65,188,127,106,34,2,65,17,75,13,38,2,64,32,2,14,18,0,39,24,39,39,39,39,39,25,39,39,39,39,39,26,39,39,27,0,11,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,28,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,196,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,28,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,9,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,196,0,58,0,0,32,0,65,2,106,33,1,12,9,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,10,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,198,0,58,0,0,32,0,65,2,106,33,1,12,10,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,11,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,204,0,58,0,0,32,0,65,2,106,33,1,12,11,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,12,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,210,0,58,0,0,32,0,65,2,106,33,1,12,12,11,2,64,32,1,65,255,1,113,34,0,65,10,70,13,0,32,0,65,50,70,13,0,32,0,65,39,71,13,13,11,65,3,16,0,34,0,32,1,58,0,1,32,0,65,213,0,58,0,0,32,0,65,2,106,33,1,12,13,11,65,3,16,0,34,0,65,194,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,194,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,196,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,198,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,204,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,210,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,2,16,0,34,0,65,213,0,58,0,0,32,0,65,1,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,4,16,0,34,0,65,198,228,40,54,0,0,32,0,15,11,65,4,16,0,34,0,65,204,228,40,54,0,0,32,0,15,11,65,4,16,0,34,0,65,210,228,40,54,0,0,32,0,15,11,65,4,16,0,34,0,65,213,228,40,54,0,0,32,0,15,11,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,6,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,198,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,6,11,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,7,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,204,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,7,11,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,8,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,210,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,8,11,2,64,32,1,65,255,1,113,34,0,65,39,70,13,0,32,0,65,10,71,13,9,11,65,4,16,0,34,0,32,1,58,0,1,32,0,65,213,0,58,0,0,32,0,65,10,58,0,2,32,0,65,3,106,33,1,12,9,11,65,3,16,0,34,0,65,196,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,3,16,0,34,0,65,198,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,3,16,0,34,0,65,204,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,3,16,0,34,0,65,210,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,3,16,0,34,0,65,213,20,59,0,0,32,0,65,2,106,33,1,11,32,1,65,0,58,0,0,32,0,15,11,65,144,1,33,0,32,2,65,190,127,106,34,1,65,19,75,13,0,2,64,32,1,14,20,0,1,2,1,3,1,1,1,1,1,4,1,1,1,1,1,5,1,1,6,0,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,194,228,0,59,0,0,11,32,0,15,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,196,228,0,59,0,0,32,0,15,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,198,228,0,59,0,0,32,0,15,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,204,228,0,59,0,0,32,0,15,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,210,228,0,59,0,0,32,0,15,11,65,3,16,0,34,0,65,0,58,0,2,32,0,65,213,228,0,59,0,0,32,0,11,155,130,128,128,0,1,7,127,65,144,1,33,4,65,0,33,5,2,64,3,64,32,5,32,0,16,2,79,13,1,65,4,16,0,33,1,65,32,33,7,65,32,33,6,2,64,32,0,16,2,32,5,77,13,0,32,0,32,5,106,44,0,0,33,6,11,32,1,32,6,58,0,0,2,64,32,0,16,2,32,5,65,1,106,34,6,77,13,0,32,0,32,5,106,65,1,106,44,0,0,33,7,11,32,1,32,7,58,0,1,65,32,33,7,2,64,32,0,16,2,32,5,65,2,106,77,13,0,32,0,32,5,106,65,2,106,44,0,0,33,7,11,32,1,65,0,58,0,3,32,1,32,7,58,0,2,32,6,33,5,32,1,16,8,34,1,16,2,65,1,72,13,0,32,1,16,7,65,3,108,65,208,0,106,34,2,16,2,34,5,32,4,16,2,34,3,106,34,7,65,1,106,16,0,33,1,2,64,32,5,65,1,72,13,0,32,1,32,2,32,5,16,1,26,11,2,64,32,3,65,1,72,13,0,32,1,32,5,106,32,4,32,7,32,5,65,1,106,34,3,32,7,32,3,74,27,32,5,107,16,1,26,11,32,1,32,7,106,65,0,58,0,0,32,1,33,4,32,6,33,5,12,0,11,11,32,4,11,133,128,128,128,0,0,65,160,1,11,138,128,128,128,0,0,65,160,1,16,9,26,65,0,11,11,159,129,128,128,0,3,0,65,16,11,54,66,0,0,70,0,0,85,0,0,68,0,0,82,0,0,76,0,0,66,39,0,70,39,0,85,39,0,68,39,0,82,39,0,76,39,0,66,50,0,70,50,0,85,50,0,68,50,0,82,50,0,76,50,0,0,65,208,0,11,54,66,39,0,70,39,0,85,39,0,68,39,0,82,39,0,76,39,0,66,0,0,70,0,0,85,0,0,68,0,0,82,0,0,76,0,0,66,50,0,70,50,0,85,50,0,68,50,0,82,50,0,76,50,0,0,65,160,1,11,33,82,50,66,70,85,68,82,76,66,39,70,39,85,39,68,39,82,39,76,39,66,50,70,50,85,50,68,50,82,50,76,50,0]);
var wasmModule = new WebAssembly.Module(wasmCode);
var wasmInstance = new WebAssembly.Instance(wasmModule, wasmImports);
let heap = new Uint8Array(wasmInstance.exports.memory.buffer);
let result = wasmInstance.exports.teste();
resultText = lib.UTF8ArrayToString(heap, result)
log(resultText);

Uncaught RangeError: WebAssembly.Compile is disallowed on the main thread, if the buffer size is larger than 4KB. Use WebAssembly.compile, or compile on a worker thread.
    at AppComponent.createWasmImports (App.tsx:399)
    at AppComponent.runHarness (App.tsx:391)
    at Object.ReactErrorUtils.invokeGuardedCallback (react.js:11110)
    at executeDispatch (react.js:2891)
    at Object.executeDispatchesInOrder (react.js:2914)
    at executeDispatchesAndRelease (react.js:2346)
    at executeDispatchesAndReleaseTopLevel (react.js:2357)
    at Array.forEach (<anonymous>)
    at forEachAccumulated (react.js:17732)
    at Object.processEventQueue (react.js:2533)
*/
