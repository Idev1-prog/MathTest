#include "math_test.h"

int generator(int min, int max) {
	return min + rand() % (max - min + 1);
}

MathTest::MathTest() {
	task.num1 = rand() % 200;
	task.num2 = rand() % 200;
	task.oper = '+';
	task.answer = task.num1 + task.num2;
}
MathTest::MathTest(int min, int max, char op) {
	task.oper = op;
	task.num1 = generator(min, max);
	task.num2 = generator(min, max);
}
