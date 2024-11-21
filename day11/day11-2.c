#include <stdio.h>
#include <math.h>

//f(x)
double f(double x) {
	return -log10(1 / x) + sin(x);
}

int main() {
	double a, b; // ���� ����
	int n, n_temp; // ���� ����

	printf("������ ���� ���� �Է��ϼ��� : ");
	scanf_s("%lf", &a);

	printf("������ �� ���� �Է��ϼ��� : ");
	scanf_s("%lf", &b);

	printf("������ �ִ� ������ �Է��ϼ���(2^n) : ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) {
		n_temp = pow(2, i);
		double wide = (b - a) / n_temp;	// �� ������ ��
		double sum = 0.0;

		// sum�� f(a)�� f(b)�� ���� ���� ����
		sum += f(a) / 2.0;
		sum += f(b) / 2.0;

		// sum�� ������ ������ �Լ� �� ���ϱ�
		for (int j = 1; j < n_temp; j++) {
			double x = a + j * wide;
			sum += f(x);
		}

		//���б����� ��� ��� ���
		double result = sum * wide;
		printf("���� %d ���� ��� : %lf\n", n_temp, result);
		
	}
}