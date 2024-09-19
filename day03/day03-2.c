#include<stdio.h>

int factorial(int n);
int main() {
	int num;
	
	printf("계산할 팩토리얼 값 입력 : ");
	scanf_s("%d", &num);

	printf("%d! = %d", num, factorial(num));

}

int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}