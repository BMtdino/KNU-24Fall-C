#include <stdio.h>
#include <math.h>

//f(x)
double f(double x) {
	return -log10(1 / x) + sin(x);
}

int main() {
	double a, b; // 적분 구간
	int n, n_temp; // 시행 구간

	printf("적분할 시작 값을 입력하세요 : ");
	scanf_s("%lf", &a);

	printf("적분할 끝 값을 입력하세요 : ");
	scanf_s("%lf", &b);

	printf("시행할 최대 구간을 입력하세요(2^n) : ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) {
		n_temp = pow(2, i);
		double wide = (b - a) / n_temp;	// 각 구간의 폭
		double sum = 0.0;

		// sum에 f(a)와 f(b)의 절반 값을 더함
		sum += f(a) / 2.0;
		sum += f(b) / 2.0;

		// sum에 나머지 구간의 함수 값 더하기
		for (int j = 1; j < n_temp; j++) {
			double x = a + j * wide;
			sum += f(x);
		}

		//구분구적법 계산 결과 출력
		double result = sum * wide;
		printf("구간 %d 적분 결과 : %lf\n", n_temp, result);
		
	}
}