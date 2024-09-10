#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define COLS 40
#define ROWS 20

char board[COLS * ROWS];

int isGameOver = 0;

void fillBoard(){
    int x,y;
    for(y=0; y<ROWS; y++){
        for(x =0; x<COLS; x++){
            if(x==COLS-1 || y==ROWS-1 || x==0 || y==0){
                board[y*COLS +x] ='#';
            }
            else {
                board[y*COLS +x] =' ';
            }
        }
    }
}

int snakeX = 5;
int snakeY = 5;

int points = 3;

struct SBody {
    int x, y;
    struct SBody* next;
};

void addBody(struct SBody* head){
    struct SBody* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    struct SBody* newBody = (struct SBody*)malloc(sizeof(struct SBody));
    newBody->x = current->x;
    newBody->y = current->y;
    newBody->next = NULL;
    current->next = newBody;

    points++;
}

void drawSnake(){
    board[snakeY*COLS + snakeX] = '@';
}

void moveSnake(int deltaX, int deltaY){
    snakeX += deltaX;
    snakeY += deltaY;
}

void readKeyboard(){
    int ch = _getch();
    if(ch == 27){

    }else {
        switch(ch){
            case 'w': moveSnake(0, -1); break;
            case 's': moveSnake(0, 1); break;
            case 'a': moveSnake(-1, 0); break;
            case 'd': moveSnake(1, 0); break;
        }
    }
}

void printBoard(){
    system("cls");
    int x,y;
    for(y=0; y<ROWS; y++){
        for(x =0; x<COLS; x++){
            _putch(board[y*COLS + x]);
        }
        _putch('\n');
    }
}

int main(int argc, char **argv){

    while(!isGameOver){
        Sleep(100);
        fillBoard();
        drawSnake();
        printBoard();
        readKeyboard();

    }

    return 0;
}
