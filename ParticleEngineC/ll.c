#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
}

struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int value){
    struct Node* newNode = createNode(value);
    if (*head == NULL){
        *head = newNode;
    } else{
        struct Node* temp = *head;
        while (temp->next! = NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
