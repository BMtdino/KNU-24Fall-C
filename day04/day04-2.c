#include<stdio.h>

void swap(int *num1, int *num2);

int main() {
	int a = 10, b = 20;

	printf("a : %d, b : %d\n", a, b);
	swap(&a, &b);
	printf("a : %d, b : %d\n", a, b);
}

void swap(int *num1, int *num2) {
	int temp1 = *num1;

	*num1 = *num2;
	*num2 = temp1;
	
}