#include<stdio.h>

int main() {
	int floor;
	int front, behind;

	printf("�� �Է� : ");
	scanf_s("%d", &floor);
	printf("%d�� �Ƕ�̵�\n", floor);
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