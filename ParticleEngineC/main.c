#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int width;
    int height;
    char *canvas;
} Display;

// Initialize the display
void init_display(Display *display, int width, int height) {
    display->width = width;
    display->height = height;
    display->canvas = (char *)malloc(width * height * sizeof(char));
    memset(display->canvas, ' ', width * height * sizeof(char));
}

void update_display(Display *display, const char *content){
    memcpy(display->canvas, content, display->width * display->height * sizeof(char));
}

void render_display(Display *display){
    for(int y =0; y< display->height; ++y){
        for(int x =0; x< display->width; ++x){
            putchar(display->canvas[y * display->width + x]);
        }
        putchar('\n');
    }
}

void wait_for_next_frame(int fps){
    int frame_time = 1000000 / fps;
    usleep(frame_time);
}


int main() {
    Display display;
    int width = 80;
    int height = 24;
    int fps = 10;

    init_display(&display, width, height);

    while(1){
        char *content 
    }
}
