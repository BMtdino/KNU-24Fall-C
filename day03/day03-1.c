#include<stdio.h>
#include<stdbool.h>

bool check_prime(int n);

int main() {
	int num;
	bool checkedNum;
	printf("�Ҽ����� Ȯ���� ���� �Է��ϼ��� : ");
	scanf_s("%d", &num);
	
	checkedNum = check_prime(num);

	if (checkedNum == true) {
		printf("�ش� ���� �Ҽ��Դϴ�.");
	}
	else {
		printf("�ش� ���� �Ҽ��� �ƴմϴ�.");
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