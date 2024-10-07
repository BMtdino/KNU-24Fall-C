#include<stdio.h>

int main() {
	int floor;
	int front, behind;

	printf("Ãþ ÀÔ·Â : ");
	scanf_s("%d", &floor);
	printf("%dÃþ ÇÇ¶ó¹Ìµå\n", floor);
	front = floor;
	behind = floor;

	for (int i = 1; i <= floor; i++) {
		for (int j = 1; j <= floor + (floor - 1); j++) {
			if (front <= j && j <= behind) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
		front--;
		behind++;
	}
}