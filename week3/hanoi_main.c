//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void hanoi(int, char, char, char);

int main() {
	int n, count = 0;
	printf("원판의 개수를 입력하시오:");
	scanf("%d", &n);

	hanoi(n, 'A', 'B', 'C');

	for (int i = 0; i < n; i++)
		count = count * 2 + 1;
	printf("총 이동 횟수: %d", count);
	return 0;
}

void hanoi(int n, char from, char middle, char to) {
	if (n == 1) {
		printf("%d번 원판을 %c에서 %c로 이동\n", n, from, to);
		return;
	}
	hanoi(n - 1, from, to, middle);
	printf("%d번 원판을 %c에서 %c로 이동\n", n, from, to);
	hanoi(n - 1, middle, from, to);
}