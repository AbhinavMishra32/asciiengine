#include <stdio.h>

#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
void printArray(int *arr, int size);
void removeElement(int *a, int n, int index);

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = SIZE(arr);

    printArray(arr, size);
    removeElement(arr,size, 2);

    int size2 = SIZE(arr);

    printArray(arr, size2);

    return 0;
}

void printArray(int *arr, int size){
    for(int i = 0; i< size; i++){
        printf("%d", arr[i]);
    }
    printf("\n");
}

void removeElement(int *a, int n, int index){
    for(int i = index; i< n-1; i++){
        a[i] = a[i+1];
    }
}

