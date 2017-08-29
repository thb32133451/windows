#include <iostream>
#include <stdlib.h>
const int LENGTH = 100;
const int B = 1000;
void sort(int n[], int length);

int main() {
	int n[LENGTH];
	
	for (int i = 0; i < LENGTH; i++) {
		n[i] =rand();
	}
	for (int show = 0; show<LENGTH; show++) {
		std::cout << n[show] << std::endl;
	}
	
	sort(n, LENGTH);

	std::cout << "And then,sort:" << std::endl;
	for (int show = 0; show<LENGTH; show++) {
		std::cout << n[show] << std::endl;
	}
	system("pause");
	return 0;
}

void sort(int n[], int length) {
	int key;
	int j;
	for (int i = 1; i<length; i++) {
		key = n[i];

		j = i - 1;
		while (j>=0 && n[j]>key) {
			n[j + 1] = n[j];
			j -= 1;
		}
		n[j + 1] = key;
	}
}
