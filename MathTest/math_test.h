#pragma once
#include <random>

struct  Task
{
	int _num1;
	int _num2;
	char _oper;
	int _answer;

	Task();
	Task(int min, int max, char op);
	~Task() = default;
};
