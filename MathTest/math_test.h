#pragma once
#include <random>
#include <algorithm>

struct Task
{
	int _num1;
	int _num2;
	char _oper;
	int _answer;

	Task();
	Task(int min, int max, char op);
	~Task() = default;
};


class MathTest
{
	Task* _tasks;
	int _tasks_count;
	int* _user_answers_count; // потенциально к удалению
	int _correct_user_answers_count;

public:
	MathTest(int tasks_count = 1);
	~MathTest();


};