#include<stdio.h>

int factorial(int n);
int main() {
	int num;
	
	printf("����� ���丮�� �� �Է� : ");
	scanf_s("%d", &num);

	printf("%d! = %d", num, factorial(num));

}

int factorial(int n) {
	if (n == 1 || n == 0) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}