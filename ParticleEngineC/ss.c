#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define COLS 40
#define ROWS 20
#define SNAKE_MAX_LEN 256

char board[COLS * ROWS];

int isGameOver = 0;

void setRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);  
    term.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &term); 

    // Make stdin non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void resetMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;  // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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

struct SnakePart{
    int x,y;
    char dir[2];
};

struct Snake snake;

struct Snake{
    int length;
    struct SnakePart part[SNAKE_MAX_LEN];
};

void drawSnake(){
    for(int i =snake.length; i>0; i--){
        board[snake.part[i].y*COLS + snake.part[i].x] = '*';
    }
    board[snake.part[0].y*COLS + snake.part[0].x] = '@';
}

void moveBody(){

    for(int i = snake.length-1; i>0; i--){
        snake.part[i] = snake.part[i-1];
    }
}

void updateSnake(){
    struct SnakePart *snakeHead = &snake.part[0];
    for(int i = 1; i<snake.length; i++){
        snake.part[i].dir[0] = snake.part[i-1].dir[0];
    }

   for(int i = snake.length-1; i>0; i--) {
        snake.part[i].x = snake.part[i-1].x;
        snake.part[i].y = snake.part[i-1].y;
    }
}

void checkCollision(){
    if (snake.part[0].x < 0 || snake.part[0].x >= COLS-1 ||
        snake.part[0].y < 0 || snake.part[0].y >= ROWS-1) {
        isGameOver = 1;
    }
    for(int i = 1; i< snake.length; i++){
        if (snake.part[0].x == snake.part[i].x && snake.part[0].y == snake.part[i].y){
            isGameOver = 1;
        }
    }
}

void readKeyboard(struct SnakePart* snakeHead){
    int ch = getchar();
    if(ch == 27){

    }else {
        switch(ch){
            case 'w' : snakeHead->dir[0] = 'u'; break;
            case 's' : snakeHead->dir[0] = 'd'; break;
            case 'a' : snakeHead->dir[0]= 'l'; break;
            case 'd' : snakeHead->dir[0]= 'r'; break;
        }
    }
}

void printBoard(){
    system("clear");
    int x,y;
    for(y=0; y<ROWS; y++){
        for(x =0; x<COLS; x++){
            putchar(board[y*COLS + x]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv){

    snake.length = 5;
    snake.part[0].x = 5;
    snake.part[0].y = 5;
    snake.part[0].dir[0] = 'r';

    int startPos[4] = {1,2,3,4};

    for(int i = 1; i<=4; i++){
        snake.part[i].x = startPos[i-1];
        snake.part[i].y = 5;
        snake.part[i].dir[0] = 'r';
    }

    setRawMode();

    while(!isGameOver){
        usleep(50000);
        fillBoard();
        checkCollision();
        drawSnake();
        printBoard();
        readKeyboard(&snake.part[0]);
        updateSnake();
    }
    resetMode();

    return 0;
}
