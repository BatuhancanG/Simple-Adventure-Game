#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

int playerP[2]={0,0};

void prepareDisplayMatrix(int row,int col,char displayMatrix[20][30],int playerP[2]){

    for(int i=0;i<20;i++){
        for(int j=0;j<30;j++){
            if((playerP[0]==i)&&(playerP[1]==j)){
                displayMatrix[i][j]='P';
            }
            else{
                displayMatrix[i][j]= -78;
            }
        }
    }
}

void preparePlacementMatrix(int row,int col,char placementMatrix[20][30],int tree_c,int* enemy_c_p){

    srand(time(0));

    int matrix_x,matrix_y;
    for(int i=0;i<20;i++){
        for(int j=0;j<30;j++){
            placementMatrix[i][j]=' ';
        }
    }
    for(int a=0;a<tree_c;a++){

        matrix_x=(rand()%29)+1;
        matrix_y=(rand()%19)+1;
        placementMatrix[matrix_y][matrix_x]='T';
    }

    for(int b=0;b<(*enemy_c_p);b++){

        matrix_x=(rand()%29)+1;
        matrix_y=(rand()%19)+1;

        placementMatrix[matrix_y][matrix_x]='E';
    }
}

void display(char displayMatrix[20][30]){
    for(int i=0;i<20;i++){
        for(int j=0;j<30;j++){
            printf("%c",displayMatrix[i][j]);
        }
        printf("\n");
    }
}

void prepareTheGame(int row,int col,char displayMatrix[20][30],char placementMatrix[20][30],int tree_c,int* enemy_c_p,int playerP[2]){

    prepareDisplayMatrix(row,col,displayMatrix,playerP);
    preparePlacementMatrix(row,col,placementMatrix,tree_c,enemy_c_p);
}

void eraseFog(int playerP[2],char displayMatrix[20][30],char placementMatrix[20][30]){

    //left
    if(playerP[1]!=0){
        if(placementMatrix[playerP[0]][playerP[1]-1]==' '){
            displayMatrix[playerP[0]][playerP[1]-1]=-80;
        }else{
            displayMatrix[playerP[0]][playerP[1]-1]=placementMatrix[playerP[0]][playerP[1]-1];
        }

        //top left
        if(placementMatrix[playerP[0]-1][playerP[1]-1]==' '){
            displayMatrix[playerP[0]-1][playerP[1]-1]=-80;
        }else{
            displayMatrix[playerP[0]-1][playerP[1]-1]=placementMatrix[playerP[0]-1][playerP[1]-1];
        }

        //bottom left
        if(placementMatrix[playerP[0]+1][playerP[1]-1]==' '){
            displayMatrix[playerP[0]+1][playerP[1]-1]=-80;
        }else{
        displayMatrix[playerP[0]+1][playerP[1]-1]=placementMatrix[playerP[0]+1][playerP[1]-1];
        }
    }

    //right
    if(playerP[1]!=29){
        if(placementMatrix[playerP[0]][playerP[1]+1]==' '){
            displayMatrix[playerP[0]][playerP[1]+1]=-80;
        }else{
            displayMatrix[playerP[0]][playerP[1]+1]=placementMatrix[playerP[0]][playerP[1]+1];
        }

        //top right
        if(placementMatrix[playerP[0]-1][playerP[1]+1]==' '){
            displayMatrix[playerP[0]-1][playerP[1]+1]=-80;
        }else{
            displayMatrix[playerP[0]-1][playerP[1]+1]=placementMatrix[playerP[0]-1][playerP[1]+1];
        }

        //bottom right
        if(placementMatrix[playerP[0]+1][playerP[1]+1]==' '){
            displayMatrix[playerP[0]+1][playerP[1]+1]=-80;
        }else{
            displayMatrix[playerP[0]+1][playerP[1]+1]=placementMatrix[playerP[0]+1][playerP[1]+1];
        }
    }

    //top
    if(playerP[0]!=0){
        if(placementMatrix[playerP[0]-1][playerP[1]]==' '){
            displayMatrix[playerP[0]-1][playerP[1]]=-80;
        }else{
            displayMatrix[playerP[0]-1][playerP[1]]=placementMatrix[playerP[0]-1][playerP[1]];
        }
    }

    //bottom
    if(playerP[0]!=19){
        if(placementMatrix[playerP[0]+1][playerP[1]]==' '){
            displayMatrix[playerP[0]+1][playerP[1]]=-80;
        }else{
            displayMatrix[playerP[0]+1][playerP[1]]=placementMatrix[playerP[0]+1][playerP[1]];
        }
    }
}

void updateDisplayMatrix(int row,int col,char displayMatrix[20][30],char placementMatrix[20][30],char character,int playerP[2]){


    switch(character){

        case 'W':
        case 'w':
            if(playerP[0]!=0){
                if(placementMatrix[playerP[0]-1][playerP[1]]==' '){
                    playerP[0]--;
                    displayMatrix[playerP[0]][playerP[1]]='P';
                    displayMatrix[playerP[0]+1][playerP[1]]=-80;
                    eraseFog(playerP,displayMatrix,placementMatrix);
                }
            }
            system("cls");
            display(displayMatrix);

        break;

        case 'S':
        case 's':
            if(playerP[0]!=19){
                if(placementMatrix[playerP[0]+1][playerP[1]]==' '){
                    playerP[0]++;
                    displayMatrix[playerP[0]][playerP[1]]='P';
                    displayMatrix[playerP[0]-1][playerP[1]]=-80;
                    eraseFog(playerP,displayMatrix,placementMatrix);
                }
            }
            system("cls");
            display(displayMatrix);
        break;

        case 'A':
        case 'a':
            if(playerP[1]!=0){
                if(placementMatrix[playerP[0]][playerP[1]-1]==' '){
                    playerP[1]--;
                    displayMatrix[playerP[0]][playerP[1]]='P';
                    displayMatrix[playerP[0]][playerP[1]+1]=-80;
                    eraseFog(playerP,displayMatrix,placementMatrix);
                }
            }
            system("cls");
            display(displayMatrix);

        break;

        case 'D':
        case 'd':
            if(playerP[1]!=29){
                if(placementMatrix[playerP[0]][playerP[1]+1]==' '){
                playerP[1]++;
                displayMatrix[playerP[0]][playerP[1]]='P';
                displayMatrix[playerP[0]][playerP[1]-1]=-80;
                eraseFog(playerP,displayMatrix,placementMatrix);
                }
            }
            system("cls");
            display(displayMatrix);
        break;
    }
}

void fightWithEnemy(int row,int col,char displayMatrix[20][30],char placementMatrix[20][30],int* enemy_c_p,char character){

    if((character=='h')||(character=='H')){
        //left
        if(placementMatrix[playerP[0]][playerP[1]-1]=='E'){
            placementMatrix[playerP[0]][playerP[1]-1]=' ';
            displayMatrix[playerP[0]][playerP[1]-1]=placementMatrix[playerP[0]][playerP[1]-1];
            (*enemy_c_p)--;

        }
        //top left
        else if(placementMatrix[playerP[0]-1][playerP[1]-1]=='E'){
            placementMatrix[playerP[0]-1][playerP[1]-1]=' ';
            displayMatrix[playerP[0]-1][playerP[1]-1]=-80;
            (*enemy_c_p)--;
        }
        //bottom left
        else if(placementMatrix[playerP[0]+1][playerP[1]-1]=='E'){
            placementMatrix[playerP[0]+1][playerP[1]-1]=' ';
            displayMatrix[playerP[0]+1][playerP[1]-1]=-80;
            (*enemy_c_p)--;
        }
        //right
        else if(placementMatrix[playerP[0]][playerP[1]+1]=='E'){
            placementMatrix[playerP[0]][playerP[1]+1]=' ';
            displayMatrix[playerP[0]][playerP[1]+1]=-80;
            (*enemy_c_p)--;
        }
        //top right
        if(placementMatrix[playerP[0]-1][playerP[1]+1]=='E'){
            placementMatrix[playerP[0]-1][playerP[1]+1]=' ';
            displayMatrix[playerP[0]-1][playerP[1]+1]=-80;
            (*enemy_c_p)--;
        }
        //bottom right
        else if(placementMatrix[playerP[0]+1][playerP[1]+1]=='E'){
            placementMatrix[playerP[0]+1][playerP[1]+1]=' ';
            displayMatrix[playerP[0]+1][playerP[1]+1]=-80;
            (*enemy_c_p)--;
        }
        //top
        else if(placementMatrix[playerP[0]-1][playerP[1]]=='E'){
            placementMatrix[playerP[0]+1][playerP[1]+1]=' ';
            displayMatrix[playerP[0]-1][playerP[1]]=-80;
            (*enemy_c_p)--;
        }
        //bottom
        else if(placementMatrix[playerP[0]+1][playerP[1]]=='E'){
            placementMatrix[playerP[0]+1][playerP[1]]=' ';
            displayMatrix[playerP[0]+1][playerP[1]]=-80;
            (*enemy_c_p)--;
        }
    }
    system("cls");
    display(displayMatrix);
}

void update(int row,int col,char displayMatrix[20][30],char placementMatrix[20][30],int* enemy_c_p){

    char character;

    while(1){

        character=getch();

        if((character=='q')||(character=='Q')){
            break;
        }
        else if(*enemy_c_p==0){
            break;
        }
        else{
             updateDisplayMatrix(20,30,displayMatrix,placementMatrix,character,playerP);
             fightWithEnemy(20,30,displayMatrix,placementMatrix,enemy_c_p,character);
             printf("%d",*enemy_c_p);
        }
    }
}

int main(){

    int tree_c,enemy_c;
    int *enemy_c_p;
    enemy_c_p=&enemy_c;
    char displayMatrix[20][30],placementMatrix[20][30];

    srand(time(NULL));
    tree_c=(rand()%7)+3;
    enemy_c=(rand()%7)+1;


    prepareTheGame(20,30,displayMatrix,placementMatrix,tree_c,enemy_c_p,playerP);
    display(displayMatrix);
    update(20,30,displayMatrix,placementMatrix,enemy_c_p);
	return(0);
}


