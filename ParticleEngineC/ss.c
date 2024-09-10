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

void moveSnake(int deltaX, int deltaY){

    for(int i = snake.length-1; i>0; i--){
        snake.part[i] = snake.part[i-1];
    }
    snake.part[0].x += deltaX; // set this equal to the global head position which is increasing every frame based on what button was pressed 
    // meaning the dx will increase every frame if last button was w
    snake.part[0].y += deltaY;
}

void updateSnake(struct SnakePart* snakeHead){
    switch(snakeHead->dir[0]){
        case 'u' : snakeHead->y -=1; break;
        case 'd' : snakeHead->y +=1; break;
        case 'l' : snakeHead->x -=1; break;
        case 'r' : snakeHead->x +=1; break;
    }
    if (snakeHead->x == COLS || snakeHead->y == ROWS)
        isGame
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

    snake.length = 10;
    snake.part[0].x = 5;
    snake.part[0].y = 5;

    setRawMode();
    int c;

    while(!isGameOver ||( c = getchar()) != 'q'){
        usleep(50000);
        fillBoard();
        drawSnake();
        printBoard();
        readKeyboard(&snake.part[0]);
        updateSnake(&snake.part[0]);

    }
    resetMode();

    return 0;
}
