#include <iostream>
#include <stdlib.h>
#include <time.h>
const unsigned long long LENGTH = 100000;
const unsigned long long A = 0;
void sort(long long n[], long long length);

int main() {
	long long n[LENGTH];
	clock_t start = clock();
	srand((unsigned)time(NULL));
	for (long long i = 0; i < LENGTH; i++) {
		n[i] = rand();
	}
	
	sort(n, LENGTH);

	std::cout << "And then,sort:" << std::endl;
	for (long long show = 0; show<LENGTH; show++) {
		std::cout << n[show] << std::endl;
	}
	clock_t ends = clock();
	std::cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << std::endl;
	std::cin.get();
	return 0;
}

void sort(long long n[], long long length) {
	long long key;
	long long j;
	for (long long i = 1; i<length; i++) {
		key = n[i];

		j = i - 1;
		while (j>=0 && n[j]>key) {
			n[j + 1] = n[j];
			j -= 1;
		}
		n[j + 1] = key;
	}
}
