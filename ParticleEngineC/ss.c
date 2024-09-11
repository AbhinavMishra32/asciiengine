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

struct SnakePart{
    int x,y;
    char dir[2];
    char prevDir;
};

struct Snake{
    int length;
    int totalmoves;
    struct SnakePart part[SNAKE_MAX_LEN];
    int startLength;
};

struct Snake snake;

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
    static int foodCounter = 0;
    foodCounter++;
    if (foodCounter >= 100) {
        int foodX = rand() % (COLS - 2) + 1;
        int foodY = rand() % (ROWS - 2) + 1;
        board[foodY * COLS + foodX] = 'O';
        if (snake.part[0].x == foodX && snake.part[0].y == foodY) {
            snake.length++;
            foodCounter = 0;
        }
    }
}

void drawSnake(){
    for(int i =snake.length; i>0; i--){
        board[snake.part[i].y*COLS + snake.part[i].x] = '*';
    }
    board[snake.part[0].y*COLS + snake.part[0].x] = '@';
}

void moveBody(){
    for(int i = snake.length-1; i>0; i--) {
        snake.part[i].x = snake.part[i-1].x;
        snake.part[i].y = snake.part[i-1].y;
    }
}

void updateSnake(){
    struct SnakePart *snakeHead = &snake.part[0];

    switch(snakeHead->dir[0]){
        case 'u':
            if (snakeHead->prevDir != 'd') snakeHead->y--;
            break;
        case 'd':
            if (snakeHead->prevDir != 'u') snakeHead->y++;
            break;
        case 'l':
            if (snakeHead->prevDir != 'r') snakeHead->x--;
            break;
        case 'r':
            if (snakeHead->prevDir != 'l') snakeHead->x++;
            break;
    }

    moveBody();
    snakeHead->prevDir = snakeHead->dir[0];
}

void checkCollision() {
    // Border collision
    if (snake.part[0].x <= 0 || snake.part[0].x >= COLS-1 ||
        snake.part[0].y <= 0 || snake.part[0].y >= ROWS-1) {
        isGameOver = 1;
        printf("Game Over: Head collided with border at (%d, %d)\n", snake.part[0].x, snake.part[0].y);
    }

    // Self collision
    if (snake.length > snake.startLength) { // Only check self-collision after the snake grows
        for (int i = 1; i < snake.length; i++) {
            if (snake.part[0].x == snake.part[i].x && snake.part[0].y == snake.part[i].y) {
                isGameOver = 1;
                printf("Game Over: Head collided with body at (%d, %d)\n", snake.part[0].x, snake.part[0].y);
            }
        }
    }
}

void readKeyboard(struct SnakePart* snakeHead){
    int ch = getchar();
    if(ch == 27){
    } else {
        switch(ch){
            case 'w': if (snakeHead->prevDir != 'd') snakeHead->dir[0] = 'u'; snake.totalmoves++; break;
            case 's': if (snakeHead->prevDir != 'u') snakeHead->dir[0] = 'd'; snake.totalmoves++; break;
            case 'a': if (snakeHead->prevDir != 'r') snakeHead->dir[0] = 'l'; snake.totalmoves++; break;
            case 'd': if (snakeHead->prevDir != 'l') snakeHead->dir[0] = 'r'; snake.totalmoves++; break;
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

    snake.length = 3;
    snake.startLength = snake.length;
    snake.part[0].x = 5;
    snake.part[0].y = 5;
    snake.part[0].dir[0] = 'r';
    snake.part[0].prevDir = 'r';

    for (int i = 1; i < snake.length; i++) {
        snake.part[i].x = snake.part[0].x - i;
        snake.part[i].y = snake.part[0].y;
        snake.part[i].dir[0] = 'r';
        snake.part[i].prevDir = 'r';
    }

    setRawMode();

    while(!isGameOver){
        usleep(50000);
        fillBoard();
        drawSnake();
        printBoard();
        readKeyboard(&snake.part[0]);
        updateSnake();
        checkCollision();
    }
    resetMode();

    return 0;
}
