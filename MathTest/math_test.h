#pragma once
#include <random>

struct  Task
{
	int num1;
	int num2;
	char oper;
	int answer;
};

class MathTest
{
	Task task;
public:
	MathTest();
	MathTest(int min, int max, char op);
	~MathTest() = default;
};