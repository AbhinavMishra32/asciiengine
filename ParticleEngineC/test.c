#include <stdio.h>
#include <stdlib.h>

struct SnakePart {
    int x, y;
    struct SnakePart *next;
};

// Function to move the snake
void moveSnake(struct SnakePart *head, int dx, int dy) {
    // Save the head's current position
    int prevX = head->x;
    int prevY = head->y;

    // Move the head
    head->x += dx;
    head->y += dy;

    // Move the rest of the body
    struct SnakePart *current = head->next;
    while (current != NULL) {
        int tempX = current->x;
        int tempY = current->y;

        current->x = prevX;
        current->y = prevY;

        prevX = tempX;
        prevY = tempY;

        current = current->next;
    }
}

// Function to print the snake
void printSnake(struct SnakePart *head) {
    struct SnakePart *current = head;
    while (current != NULL) {
        printf("Part at (%d, %d)\n", current->x, current->y);
        current = current->next;
    }
}

int main() {
    // Initialize snake with 3 parts
    struct SnakePart *head = malloc(sizeof(struct SnakePart));
    struct SnakePart *second = malloc(sizeof(struct SnakePart));
    struct SnakePart *third = malloc(sizeof(struct SnakePart));

    head->x = 5; head->y = 5; head->next = second;
    second->x = 5; second->y = 6; second->next = third;
    third->x = 5; third->y = 7; third->next = NULL;

    // Print initial snake position
    printf("Initial snake position:\n");
    printSnake(head);

    // Move the snake (for example, up with dx=0, dy=-1)
    moveSnake(head, 0, -1);

    // Print new snake position
    printf("\nAfter moving up:\n");
    printSnake(head);

    // Free allocated memory
    free(third);
    free(second);
    free(head);

    return 0;
}

