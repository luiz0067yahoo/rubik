#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define BLUE 0
#define GREEN 1
#define WHITE 2
#define YELLOW 3
#define ORANGE 4
#define RED 5

char colors[6][7] ={"b", "g", "w", "y", "o", "r"};
char digits[10][2] ={"0","1","2","3","4","5","6","7","8","9"};
char moviments[18][3] ={"B","F","U","D","R","L","B'","F'","U'","D'","R'","L'","B2","F2","U2","D2","R2","L2"};

char *pieces [6][3][3];
char *piecesState [6][3][3];

int abs(int X){
    return ((X>=0)? X : -(X) );
}

int round(float X){
    return  (X>=0)? (int) (X + 0.5) : (int)-(abs(X) +0.5);
}

char* string_substring(char *str, int start, int end) {
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

int string_equals(char *a,char *b){
    int size_a=strlen(a);
    int size_b=strlen(b);
    int count=-1;
    if(size_a==size_b){
        count=1;
        for(int i=0;i<size_a-1;i++){
            if(a[i]==b[i]){
               count++;
            }
        }
    }
    return count==size_a;
}

int string_indexOf(char *text,char *word_){
	int T_text,T_word_;
	T_word_= strlen(word_);
	T_text = strlen(text);
	for (int i=0;i<T_text-T_word_;i++)
	{
		char *acc;
		acc=string_substring(text,i,i+T_word_);
		if(string_equals(word_,acc)){
            break;
            return i;
		}
	}
	return -1;
}

int string_count(char *text,char *word_){
	int T_text,T_word_,count;
	T_word_= strlen(word_);
	T_text = strlen(text);
	count=0;
	count=T_text;
	for (int i=0;i<T_text-T_word_;i++)
	{
		char *acc;
		acc=string_substring(text,i,i+T_word_);
		if(string_equals(word_,acc)){
            count++;
		}
	}
	return count;
}

int string_countChar(char *text,char word_){
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

char* string_line(char *text,int line_number){
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
    line=string_substring(text,start,end);
    return line;
}

char* string_concat(char *a,char *b){
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

char *createMove(){
    ////srand( (unsigned)time(NULL) );
    return moviments[ rand() % 18];
}

char *trimCommand(char *tcommand){
  char *ttrim="";
  int i=0;
  char *last_command="";
  if (strlen(tcommand)>0)
  while(1==1){
    char *command="";
    char acc1,acc2;
    acc1=(strlen(tcommand)>i)?tcommand[i]:' ';
    acc2=(strlen(tcommand)>i+1)?tcommand[i+1]:' ';
    if(acc1!='\n'){
        //i++;
    }
    if((acc1!=' ')&&((acc2=='2')||(acc2=='\''))){
        command=malloc(3);
        command[0]=acc1;
        command[1]=acc2;
        command[2]='\0';
        i++;
    }
    if((acc1!=' ')&&((acc2!='2')&&(acc2!='\''))){
        command=malloc(2);
        command[0]=acc1;
        command[1]='\0';
    }
    i++;
    if(
       (strlen(command)==strlen(last_command))
       &&
       (
           (
               (strlen(command)==2)
               &&
               (command[0]==last_command[0])
               &&
               (command[1]==last_command[1])
            )
            ||
            (strlen(command)==1)
        )
       )
    {
        if(acc2=='2'){//u2u2
            command="";
            ttrim=string_substring(ttrim,0,strlen(ttrim)-2);
        }
        else if(acc2=='\''){//u'u'
            command=malloc(3);
            command[0]=acc1;
            command[1]='2';
            command[2]='\0';
            ttrim=string_substring(ttrim,0,strlen(ttrim)-2);
        }
        else if((acc2!='\'')&&(acc2!='2')){//uu
            command="2";
        }
    }
    else if(
        (strlen(last_command)>0)
        &&
        (strlen(command)>0)
        &&
        (command[0]==last_command[0])
    ){
        if((acc2=='\'')&&(strlen(last_command)==1)){//uu'
            command="";
            ttrim=string_substring(ttrim,0,strlen(ttrim)-1);
        }
        else if((strlen(last_command)==2)&&(strlen(command)==1)&&(last_command[1]=='\'')&&(acc2!='2')){//u'u
            command="";
            ttrim=string_substring(ttrim,0,strlen(ttrim)-2);
        }
        else if((strlen(last_command)==2)&&(strlen(command)==2)&&(last_command[1]=='\'')&&(acc2=='2')){//u'u2
            command="";
            ttrim=string_substring(ttrim,0,strlen(ttrim)-1);
        }
        else if((strlen(last_command)==1)&&(acc2=='2')){//uu2
            command="'";
        }
        else if((strlen(last_command)==2)&&(strlen(command)==1)&&(last_command[1]=='2')){//u2u
            command="'";
            ttrim=string_substring(ttrim,0,strlen(ttrim)-1);
        }
        else if((strlen(last_command)==1)&&(acc2=='2')){//u2u'
            command="'";
        }
    }
    ttrim=string_concat(ttrim,command);
    last_command=command;
    if (i>=strlen(tcommand)) break;

  }
  return ttrim;
}

int *shuffleNumber(int x){
    int numbers_[x];//=malloc(x);
    //=malloc(x);
    for (int i=0;i<x;i++){
        int count=0;
        ////srand( (unsigned)time(NULL) );
        int acc=rand() % (x);

        int find_number=0;
        while(find_number>0){
            int acc_test;
            for (int j=0;j<=i;j++){
               if(numbers_[j]==acc){
                    acc_test=rand() % (x);
                    find_number++;
               }
            }
            acc=acc_test;
        }
        numbers_[i]=acc;

    }
    return numbers_;
}

char *invertPopulation(char *population){
    char *result=population;
    int count_line=string_countChar(population,'\n');
    count_line++;
    int Numbers_[count_line];
    *Numbers_=shuffleNumber(count_line);

    for(int i=0;i<count_line;i++){
        char *element=string_line(population,Numbers_[i]);
        //char *element=string_line(population,count_line-i-1);

        if(i==0)
            result=element;
        else{
            result=string_concat(result,"\n");
            result=string_concat(result,element);
        }
    }
    return result;
}

char *shuffle(int x){
    char *t_commands;
    t_commands="";
    for (int i=0;i<x;i++){
        t_commands=string_concat(t_commands,createMove());
        while(strlen(t_commands) > strlen(trimCommand(t_commands))){
            t_commands=trimCommand(t_commands);
            x++;
        }
    }
    return t_commands;
}

char *generateName(int face,int height,int width){
    int pos=(3*height+width)+1;
    char *name=string_concat(colors[face],digits[pos]);
    name=string_concat(name," ");
    return name;
}

void CubeInitializer(){
     for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                pieces[face][height][width]=generateName(face,height,width);
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

void CubePrint(){
    int face=2;
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
    for ( int height=0; height<3; height++ ){
        face=4;
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        face=0;
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        face=5;
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        printf("\n");
    }
    face=3;
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
    face=1;
    for ( int height=0; height<3; height++ ){
        printf("         ");
        for ( int width=0; width<3; width++ ){
            printf("%s",pieces[face][height][width]);
        }
        printf("         ");
        printf("\n");
    }
}

void CubeMove(char *str){
    if(strlen(str)==1){
        if(str[0]=='R'){
            moveR();
        }
        else if(str[0]=='L'){
            moveL();
        }
        else if(str[0]=='U'){
            moveU();
        }
        else if(str[0]=='D'){
            moveD();
        }
        else if(str[0]=='F'){
            moveF();
        }
        else if(str[0]=='B'){
            moveB();
        }
    }
    else if((strlen(str)==2)&&(str[1]=='\'')){
        if(str[0]=='R'){
            moveR_Back();
        }
        else if(str[0]=='L'){
            moveL_Back();
        }
        else if(str[0]=='U'){
            moveU_Back();
        }
        else if(str[0]=='D'){
            moveD_Back();
        }
        else if(str[0]=='F'){
            moveF_Back();
        }
        else if(str[0]=='B'){
            moveB_Back();
        }
    }
    else if((strlen(str)==2)&&(str[1]=='2')){
        for ( int i=0; i<2; i++ ){
            if(str[0]=='R'){
                moveR();
            }
            else if(str[0]=='L'){
                moveL();
            }
            else if(str[0]=='U'){
                moveU();
            }
            else if(str[0]=='D'){
                moveD();
            }
            else if(str[0]=='F'){
                moveF();
            }
            else if(str[0]=='B'){
                moveB();
            }
        }
    }
}

void moveR(){
    char *pieces_move [3];
    int face=0;
    int width=0;
    for ( int height=0; height<3; height++ ){//store blue face
        pieces_move[height]=pieces[BLUE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change blue to white
        pieces[BLUE][height][width]=pieces[WHITE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change white to green
        pieces[WHITE][height][width]=pieces[GREEN][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change green to yellow
        pieces[GREEN][height][width]=pieces[YELLOW][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to blue moved
        pieces[YELLOW][height][width]=pieces_move[height];
    }
}

void moveR_Back(){
    char *pieces_move [3];
    int face=0;
    int width=0;
    for ( int height=0; height<3; height++ ){//store blue face
        pieces_move[height]=pieces[BLUE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to blue moved
        pieces[BLUE][height][width]=pieces[YELLOW][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to green
        pieces[YELLOW][height][width]=pieces[GREEN][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change green to white
        pieces[GREEN][height][width]=pieces[WHITE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change white to blue moved
        pieces[WHITE][height][width]=pieces_move[height];
    }
}

void moveL(){
    char *pieces_move [3];
    int face=0;
    int width=2;
    for ( int height=0; height<3; height++ ){//store blue face
        pieces_move[height]=pieces[BLUE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to blue moved
        pieces[BLUE][height][width]=pieces[YELLOW][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to green
        pieces[YELLOW][height][width]=pieces[GREEN][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change green to white
        pieces[GREEN][height][width]=pieces[WHITE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change white to blue moved
        pieces[WHITE][height][width]=pieces_move[height];
    }
}

void moveL_Back(){
    char *pieces_move [3];
    int face=0;
    int width=2;
    for ( int height=0; height<3; height++ ){//store blue face
        pieces_move[height]=pieces[BLUE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change blue to white
        pieces[BLUE][height][width]=pieces[WHITE][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change white to green
        pieces[WHITE][height][width]=pieces[GREEN][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change green to yellow
        pieces[GREEN][height][width]=pieces[YELLOW][height][width];
    }
    for ( int height=0; height<3; height++ ){  //change yellow to blue moved
        pieces[YELLOW][height][width]=pieces_move[height];
    }
}

void moveU(){
    char *pieces_move [3];
    int face=0;
    int height=0;
    for ( int width=0; width<3; width++ ){//store blue face
        pieces_move[width]=pieces[BLUE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change blue to red
        pieces[BLUE][height][width]=pieces[RED][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change red to green
        pieces[RED][height][width]=pieces[GREEN][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change green to orange
        pieces[GREEN][height][width]=pieces[ORANGE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change orange to blue moved
        pieces[ORANGE][height][width]=pieces_move[width];
    }
}

void moveU_Back(){
    char *pieces_move [3];
    int face=0;
    int height=0;
    for ( int width=0; width<3; width++ ){//store blue face
        pieces_move[width]=pieces[BLUE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change blue to orange
        pieces[BLUE][height][width]=pieces[ORANGE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change orange to green
        pieces[ORANGE][height][width]=pieces[GREEN][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change green to red
        pieces[GREEN][height][width]=pieces[RED][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change red to blue moved
        pieces[RED][height][width]=pieces_move[width];
    }
}

void moveD(){
    char *pieces_move [3];
    int face=0;
    int height=2;
    for ( int width=0; width<3; width++ ){//store blue face
        pieces_move[width]=pieces[BLUE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change blue to orange
        pieces[BLUE][height][width]=pieces[ORANGE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change orange to green
        pieces[ORANGE][height][width]=pieces[GREEN][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change green to red
        pieces[GREEN][height][width]=pieces[RED][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change red to blue moved
        pieces[RED][height][width]=pieces_move[width];
    }
}

void moveD_Back(){
    char *pieces_move [3];
    int face=0;
    int height=2;
    for ( int width=0; width<3; width++ ){//store blue face
        pieces_move[width]=pieces[BLUE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change blue to red
        pieces[BLUE][height][width]=pieces[RED][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change red to green
        pieces[RED][height][width]=pieces[GREEN][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change green to orange
        pieces[GREEN][height][width]=pieces[ORANGE][height][width];
    }
    for ( int width=0; width<3; width++ ){  //change orange to blue moved
        pieces[ORANGE][height][width]=pieces_move[width];
    }
}

void moveF(){
     char *pieces_move [3];
    int face=2;
    int height=0;
    int width=0;
    for (width=0; width<3; width++ ){//store  white
        pieces_move[width]=pieces[WHITE][height][width];
    }
    for (int i=0; i<3; i++ ){  //change white to red
        pieces[WHITE][0][i]=pieces[RED][i][2];
    }
    for (int i=0; i<3; i++ ){  //change red to yellow
        pieces[RED][i][2]=pieces[YELLOW][2][2-i];
    }
    for (int i=0; i<3; i++ ){  //change yellow to orange
        pieces[YELLOW][2][i]=pieces[ORANGE][i][0];
    }
    for (int i=0; i<3; i++ ){  //change orange to white store
        pieces[ORANGE][i][0]=pieces_move[2-i];
    }
}

void moveF_Back(){
    char *pieces_move [3];
    int face=2;
    int height=0;
    int width=0;
    for (width=0; width<3; width++ ){//store  white
        pieces_move[width]=pieces[WHITE][height][width];
    }
    for (int i=0; i<3; i++ ){  //change white to orange
        pieces[WHITE][0][i]=pieces[ORANGE][2-i][0];
    }
    for (int i=0; i<3; i++ ){  //change orange to yellow
        pieces[ORANGE][i][0]=pieces[YELLOW][2][i];
    }
    for (int i=0; i<3; i++ ){  //change yellow to red
        pieces[YELLOW][2][i]=pieces[RED][2-i][2];
    }
    for (int i=0; i<3; i++ ){  //change red to white store
        pieces[RED][i][2]=pieces_move[i];
    }
}

void moveB(){
    char *pieces_move [3];
    int face=2;
    int height=0;
    int width=0;
    for (width=0; width<3; width++ ){//store  white
        pieces_move[width]=pieces[WHITE][height][width];
    }
    for (int i=0; i<3; i++ ){  //change white to red
        pieces[WHITE][0][i]=pieces[RED][i][2];
    }
    for (int i=0; i<3; i++ ){  //change red to yellow
        pieces[RED][i][2]=pieces[YELLOW][2][i];
    }
    for (int i=0; i<3; i++ ){  //change yellow to orange
        pieces[YELLOW][2][i]=pieces[ORANGE][i][0];
    }
    for (int i=0; i<3; i++ ){  //change orange to white store
        pieces[ORANGE][i][0]=pieces_move[i];
    }
}

void moveB_Back(){
    char *pieces_move [3];
    int face=2;
    int height=0;
    int width=0;
    for (width=0; width<3; width++ ){//store  white
        pieces_move[width]=pieces[WHITE][height][width];
    }
    for (int i=0; i<3; i++ ){  //change white to orange
        pieces[WHITE][0][i]=pieces[ORANGE][i][0];
    }
    for (int i=0; i<3; i++ ){  //change orange to yellow
        pieces[ORANGE][i][0]=pieces[YELLOW][2][i];
    }
    for (int i=0; i<3; i++ ){  //change yellow to red
        pieces[YELLOW][2][i]=pieces[RED][i][2];
    }
    for (int i=0; i<3; i++ ){  //change red to white store
        pieces[RED][i][2]=pieces_move[i];
    }
}

char *extractCommand(char *command){
    char *ResultCommand="";
    char basicCommand[6]={'B','F','U','D','R','L'};
    char variantsCommand[2]={'\'','2'};
    char acc1=(strlen(command)>0)?command[0]:' ';
    char acc2=(strlen(command)>1)?command[1]:' ';
    for ( int i=0; i<6; i++ ){
        if(basicCommand[i]==acc1){
            if((variantsCommand[0]==acc2)||(variantsCommand[1]==acc2)){
                ResultCommand=malloc(2);
                ResultCommand[0]=acc1;
                ResultCommand[1]='\0';
            }
            else{
                ResultCommand=malloc(3);
                ResultCommand[0]=acc1;
                ResultCommand[1]=acc2;
                ResultCommand[2]='\0';
            }
        }

    }
    printf("%s\n",ResultCommand);
    return ResultCommand;
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



//####################################################################### GENETIC ALGORITIM ######################################################################################################
char *generatePopulation(int limitLength,int chromosomesLength){
    char *population;
    for (int i=0;i<limitLength;i++){
        char *element;
        element=shuffle(chromosomesLength);
        if(i==0){
            population=element;
        }
        else{
            population=string_concat(population,"\n");
            population=string_concat(population,element);
        }
    }
    return population;
}

float cubeScore(){
	float count=0;
	for ( int face=0; face<6; face++ ){
        for ( int height=0; height<3; height++ ){
            for ( int width=0; width<3; width++ ){
                int pos=(3*height+width)+1;
                char *name;
                name=colors[face];
                if (string_equals(pieces[face][height][width],generateName(face,height,width)))
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

char *select(char *population,float score){
    char *populationSelect="";
    int count_line=string_countChar(population,'\n');
    for(int i=0;i<=count_line;i++){
        char *element=string_line(population,i);
        executeCommands(element);
        float score_element=cubeScore();
        cubeLoadState();
        if(score_element>=score){
            if(i==0)
                populationSelect=element;
            else{
                populationSelect=string_concat(populationSelect,"\n");
                populationSelect=string_concat(populationSelect,element);
            }
        }
    }
    return populationSelect;
}

char *crossOver(char *population,float percert_cross){
    char *population_cross=invertPopulation(population);
    char *population_result="";
    int percert_int=round(percert_cross*100);
    int points[percert_int];
    int countCommand=0;
    int i=0;
    int j=0;
    char *accCommand="";
    char *command="";
    char *accCommand_cross="";
    char *command_cross="";
    if (strlen(population)>0)
    while(1==1){
        accCommand=malloc(3);
        accCommand[0]=(strlen(population)>i)?population[i]:' ';
        accCommand[1]=(strlen(population)>i+1)?population[i+1]:' ';
        accCommand[2]='\0';
        accCommand=extractCommand(accCommand);
        if(strlen(accCommand)>0){
            countCommand++;
            command=accCommand;
        }
        accCommand_cross=malloc(3);
        accCommand_cross[0]=(strlen(population_cross)>j)?population_cross[j]:' ';
        accCommand_cross[1]=(strlen(population_cross)>j+1)?population_cross[j+1]:' ';
        accCommand_cross[2]='\0';
        accCommand_cross=extractCommand(accCommand_cross);
        if(strlen(accCommand_cross)>0)
            command_cross=accCommand_cross;
        {
            if(countCommand%100==0){
                for(int y=0;y<percert_int;y++){
                    points[y]=rand() % 100;
                }

            }
            for(int y=0;y<percert_int;y++){
                if(points[y]==(countCommand%100)){
                    population_result=string_concat(population_result,command_cross);
                }
                else
                    population_result=string_concat(population_result,command);
            }
        }
        i++;
        j++;
        if ((i>strlen(population)) && (i>strlen(population_cross))) break;
    }
    return population_result;
}

char *mutation(char *population,float percent_mutation){
    char *population_result="";
    int percert_int=round(percent_mutation*100);
    int points[percert_int];
    int countCommand=0;
    int i=0;
    char *accCommand="";
    char *command="";
    char *lastCommand="";
    char *testCommand="";
    char *newCommand="";
    if (strlen(population)>0)
    for(int i=0;i<strlen(population);i++){
        accCommand=malloc(3);
        accCommand[0]=(strlen(population)>i)?population[i]:' ';
        accCommand[1]=(strlen(population)>i+1)?population[i+1]:' ';
        accCommand[2]='\0';
        accCommand=extractCommand(accCommand);
        if(strlen(accCommand)>0){
            countCommand++;
            command=accCommand;
        }

        {
            if(countCommand%100==0){
                for(int y=0;y<percert_int;y++){
                    points[y]=rand() % 100;
                }
            }
            for(int y=0;y<percert_int;y++){
                if(points[y]==(countCommand%100)){
                    population_result=string_concat(population_result,command);
                }
                else{
                    newCommand=createMove();
                    testCommand=" ";
                    while(strlen(testCommand)==0){
                        testCommand=string_concat(lastCommand,newCommand);
                        testCommand=trimCommand(testCommand);
                        newCommand=createMove();
                    }
                    population_result=string_concat(population_result,newCommand);
                }
            }
        }

        lastCommand=command;

    }
    return population_result;
}

char *solver(char * commands,int limitLength,int chromosomesLength,float score,float percent_mutation,float percert_cross,int gerations){
    char *population="" ;
    for(int i=0;i<gerations;i++)
    {
        CubeInitializer();
        executeCommands(commands);
        cubeSaveState();
        population=generatePopulation(limitLength,chromosomesLength);
        population=select(population,score);
        //population=mutation(population,percent_mutation);
        //population=crossOver(population,percert_cross);
        //while(strlen(population)>=chromosomesLength)
        {
            //population=select(population,1);

            //CubePrint();
            //break;
        }
    }
    return population;
}
char* teste(){
    char* command="R'D2DF'L'DF'RRL'U2B'BR'RU2RRU2D'U2D2R2U2B2D2";
    //command="RDD";
    executeCommands(command);
    int limitLength=10;
    int chromosomesLength=26;
    float score=0.6;
    float percent_mutation=0.03;
    float percert_cross=0.03;
    int gerations=1;
    printf("%s","\n");
    printf("%s","##############################");
    printf("%s","\n");
    char *population=solver(command,limitLength,chromosomesLength,score,percent_mutation,percert_cross,gerations);
    printf("%s","\n");
    printf("%s","##############################");
    printf("%s","\n");
    printf("%s",population);
    printf("%s","\n");

}
int main()
{
    teste();
    char *str;
    scanf("%[^\n]", str);
    return 0;
}
