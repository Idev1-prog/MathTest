#include <iostream>
#include <locale>
#include "math_test.h"
#include <time.h>

int main() {
	srand(time(nullptr));
	setlocale(LC_ALL, "Rus");
	MathTest test(10, 10, 11);
	test.run();
	return 200;
}