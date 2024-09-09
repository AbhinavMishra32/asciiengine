#include <stdio.h>

#define COLS 10
#define ROWS 10

char board[COLS * ROWS];

void fillBoard(){
    int x,y;
    for(y=0; y<ROWS; y++){
    for(x =0; x<COLS; x++){
        if(x==0 || y==0 || x==COLS -1 || y==ROWS -1){
                board[y*COLS +x] ='#';
            }

        }
    }
}


void printBoard(){
    int x,y;
    for(y=0; y<ROWS; y++){
        for(x =0; x<COLS; x++){
            putchar (board[y*COLS + x]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv){

    fillBoard();
    printBoard();

    return 0;
}
