#include<stdio.h>

int main() {


	for (int i = 0; i < 100; i++) {
		if(i % 12 == 0){
			printf("%d\n", i);
		}
		else if (i % 7 == 0) {
			printf("%d\n", i);
		}
	}
}