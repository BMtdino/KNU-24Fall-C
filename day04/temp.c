#include<stdio.h>

int main() {
	char a = 'A';
	int num = 356;

	char* ptr1 = &a;
	int* ptr2 = &num;

	printf("%c\n", a);
	printf("%d\n", num);

	printf("%c\n", *ptr1);
	printf("%d\n", *ptr2);
}