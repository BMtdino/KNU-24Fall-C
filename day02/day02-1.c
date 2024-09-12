#include<stdio.h>

int main() {
	double a, b;
	int menu;

	printf("원하는 기능을 입력하시오.\n");
	printf("1. 더하기 2. 빼기 3. 곱하기 4. 나누기\n");
	printf("기능 : ");
	scanf_s("%d", &menu);
	printf("숫자 1을 입력하세요 : ");
	scanf_s("%lf", &a);
	printf("숫자 2을 입력하세요 : ");
	scanf_s("%lf", &b);

	if (menu == 1) {
		printf("%lf + %lf = %lf", a, b, a + b);
	}
	else if (menu == 2) {
		printf("%lf - %lf = %lf", a, b, a - b);
	}
	else if (menu == 3) {
		printf("%lf * %lf = %lf", a, b, a * b);
	}
	else if (menu == 4) {
		printf("%lf / %lf = %lf", a, b, a / b);
	}
}