#include<stdio.h>
#include<stdbool.h>

bool check_prime(int n);

int main() {
	int num;
	bool checkedNum;
	printf("소수인지 확인할 수를 입력하세요 : ");
	scanf_s("%d", &num);
	
	checkedNum = check_prime(num);

	if (checkedNum == true) {
		printf("해당 수는 소수입니다.");
	}
	else {
		printf("해당 수는 소수가 아닙니다.");
	}
}

bool check_prime(int n) {
	if (n == 1) {
		return 0;
	}
	else if (n == 2 || n == 3 || n == 5 || n == 7) {
		return 1;
	}
	else {
		for (int i = 2; i <= n-1; i++) {
			if (n % i == 0) {
				return 0;
			}
		}
		return 1;
	}

}