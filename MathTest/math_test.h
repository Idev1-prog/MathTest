#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <string>
#include <array>

enum Operator {
	Plus, Minus, Multiply, Divide
};

struct Task
{
	int _num1;
	int _num2;
	Operator _oper;
	int _answer;

	Task();
	Task(int min, int max);
	Task(int min, int max, Operator op);
	char get_char_oper() const noexcept;
	~Task() = default;
};

class MathTest
{
	Task* _tasks;
	int _tasks_count;
	int* _user_answers;
	int _correct_user_answers_count;
	std::vector<bool> _user_answers_statuses;
	int _max_task_width = 0;
	std::string parse_to_string(int index) const noexcept;
	void calculate_max_task_width() noexcept;
public:
	MathTest(int tasks_count = 1);
	MathTest(int tasks_count, int min_num, int max_num);
	MathTest(int tasks_count, int min_num, int max_num, const Operator* opers);
	MathTest(const MathTest&) = delete;
	MathTest(MathTest&&) = delete;
	Task* get_tasks() noexcept {
		return _tasks;
	}
	int get_tasks_count() const noexcept {
		return _tasks_count;
	}
	int get_correct_count() const {
		return _correct_user_answers_count;
	}

	int get_user_answer(int index) const {
		return _user_answers[index];
	}

	bool get_answer_status(int index) const {
		return _user_answers_statuses[index];
	}
	~MathTest() {
		delete[] _tasks;
		delete[] _user_answers;
		_tasks = nullptr;
		_user_answers = nullptr;
		_tasks_count = 0;
		_correct_user_answers_count = 0;
	}
	void assign_user_task();
	void add_user_response(int user_answer, int num_of_question);
	void show_statistics();
	void run();

	MathTest& operator=(const MathTest&) = delete;
	MathTest& operator=(MathTest&&) = delete;
};