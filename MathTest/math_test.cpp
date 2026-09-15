#include "math_test.h"

int generator(int min, int max) {
	return min + rand() % (max - min + 1);
}

int calculate_with_char_operator(int num1, int num2, char op) {
	switch (op) {
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	default:
		throw std::invalid_argument("Invalid operation argument");
	}
}

Task::Task() {
	_num1 = rand() % 200;
	_num2 = rand() % 200;
	_oper = '+';
	_answer = _num1 + _num2;
}
Task::Task(int min, int max, char op) {
	_oper = op;
	_num1 = generator(min, max);
	_num2 = generator(min, max);
	_answer = calculate_with_char_operator(_num1, _num2, _oper);
}