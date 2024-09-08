#include <stdio.h>
#include <unistd.h>

int main() {
    int choice;

    printf("1. Rock\n2. Paper\n3. Scissors");
    scanf("%d", &choice);

    while (choice< 1 || choice> 3){
        printf("Invalid choice. Please enter a valid choice:");
        scanf("%d", &choice);
    }
    printf("You chose: %d", choice);

    printf("\nComputer is choosing...");
    fflush(stdout);
    sleep(2);


    int a[10] = {1,2,3,4,5,6,7,8,9,10};

    return 0;
}

void rem(int *a, int n, int index){
}