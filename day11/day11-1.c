#include <stdio.h>
#include <math.h>

int main() {
	double a, b, c;

	//���������� ��� �Է�
	printf("������������ ����� �Է��ϼ��� (a, b, c): ");
	scanf("%lf %lf %lf", &a, &b, &c);

	double delta = b * b - 4 * a * c;

	if (delta < 0) {
		printf("����� �����մϴ�.");
	}
	else if (delta == 0) {
		double root = -b / (2 * a);
		printf("�߱�: x = %.2f\n", root);
	}
	else {
		double root1 = (-b + sqrt(delta)) / (2 * a);
		double root2 = (-b - sqrt(delta)) / (2 * a);
		printf("���� �ٸ� �Ǳ�: x1 = %.2f, x2 = %.2f\n", root1, root2);
	}
}
