#include<stdio.h>

int main() {
	double a, b;
	int menu;

	printf("���ϴ� ����� �Է��Ͻÿ�.\n");
	printf("1. ���ϱ� 2. ���� 3. ���ϱ� 4. ������\n");
	printf("��� : ");
	scanf_s("%d", &menu);
	printf("���� 1�� �Է��ϼ��� : ");
	scanf_s("%lf", &a);
	printf("���� 2�� �Է��ϼ��� : ");
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