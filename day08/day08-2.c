#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10  

void fillRandom(int array[SIZE][SIZE]) {
    srand(time(NULL));  
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i][j] = rand() % 20 + 1;  
        }
    }
}

void printArray(int array[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}

void movePointer(void* array) {
    int x = 0, y = 0;  
    int steps;
    int total_elements = SIZE * SIZE;
    int* ptr = (int*)array;

    while (1) {
        printf("현재 위치: (%d, %d), 배열의 값: %d\n", x, y, *(ptr + x * SIZE + y));

        steps = *(ptr + x * SIZE + y);
        int new_x = (x * SIZE + y + steps) / SIZE;
        int new_y = (x * SIZE + y + steps) % SIZE;

        if (new_x < 0 || new_x >= SIZE || new_y < 0 || new_y >= SIZE) {
            printf("더 이상 이동할 수 없습니다. \n종료 위치: (%d, %d), 배열의 값: %d\n", x, y, *(ptr + x * SIZE + y));
            break;
        }

        x = new_x;
        y = new_y;
    }
}

int main() {
    int array[SIZE][SIZE];

    fillRandom(array);

    printArray(array);

    movePointer(array);

    return 0;
}
