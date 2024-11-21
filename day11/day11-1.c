#include <stdio.h>
#include <math.h>

int main() {
	double a, b, c;

	//이차방정식 계수 입력
	printf("이차방정식의 계수를 입력하세요 (a, b, c): ");
	scanf("%lf %lf %lf", &a, &b, &c);

	double delta = b * b - 4 * a * c;

	if (delta < 0) {
		printf("허근이 존재합니다.");
	}
	else if (delta == 0) {
		double root = -b / (2 * a);
		printf("중근: x = %.2f\n", root);
	}
	else {
		double root1 = (-b + sqrt(delta)) / (2 * a);
		double root2 = (-b - sqrt(delta)) / (2 * a);
		printf("서로 다른 실근: x1 = %.2f, x2 = %.2f\n", root1, root2);
	}
}
