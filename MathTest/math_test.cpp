#include "math_test.h"
const int* exluded_ASCII_values_for_operators = new int[2]{ 44, 46 }; // временное решение, ожидает исправления

int generator(int min, int max, bool excluded_values_count = 0, const int* exluded_values = nullptr) {
	if (excluded_values_count == 0)
		return min + rand() % (max - min + 1);
	else {
		std::vector<int> excluded_values_vec(exluded_values, exluded_values + excluded_values_count);
		int ex;
		do {
			ex = min + rand() % (max - min + 1);
		} while (std::find(excluded_values_vec.begin(), excluded_values_vec.end(), ex) != excluded_values_vec.end());
		return ex;
	}
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

MathTest::MathTest(int tasks_count) : _tasks_count(tasks_count) {
	_tasks = new Task[_tasks_count];
	_user_answers_count = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++){
		_tasks[i] = Task(0, 20, generator(42, 47, true, exluded_ASCII_values_for_operators));
	}
}

MathTest::~MathTest()
{
}