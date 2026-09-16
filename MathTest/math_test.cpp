#include "math_test.h"

const int* exluded_ASCII_values_for_operators = new int[2]{ 44, 46 }; // временное решение, ожидает исправления (счетчик костылей +1)


int generator(int min, int max, int excluded_values_count = 0, const int* exluded_values = nullptr) {
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
	if (op == '/' && _num2 == 0) _num2 = 1; // счетчик костылей +1
	_answer = calculate_with_char_operator(_num1, _num2, _oper);
}

void MathTest::calculate_max_task_wight() {
	for (int i = 0; i < _tasks_count; i++) {
		std::string str_task = parse_to_string(i);
		if (str_task.size() > _max_task_wight) _max_task_wight = str_task.size();
	}
}

std::string MathTest::parse_to_string(int index) {
	return std::to_string(_tasks[index]._num1) + _tasks[index]._oper + std::to_string(_tasks[index]._num2);
}

MathTest::MathTest(int tasks_count) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++){
		_tasks[i] = Task(0, 20, generator(42, 47, 2, exluded_ASCII_values_for_operators));
	}
	calculate_max_task_wight();
}

MathTest::MathTest(int tasks_count, int min_num, int max_num) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++) {
		_tasks[i] = Task(min_num, max_num, generator(42, 47, 2, exluded_ASCII_values_for_operators));
	}
	calculate_max_task_wight();
}

MathTest::MathTest(int tasks_count, int min_num, int max_num, const char* opers) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++) {
		_tasks[i] = Task(min_num, max_num, opers[i]);
	}
	calculate_max_task_wight();
}

void MathTest::assign_user_task() {
	for (int i = 0; i < _tasks_count; i++) {
		int user_answer;
		std::cout << "Вопрос номер " << i + 1 << ": " << _tasks[i]._num1 << ' ' << _tasks[i]._oper << ' ' << _tasks[i]._num2 << std::endl;
		std::cout << "Ваш ответ: ";
		std::cin >> user_answer;
		std::cout << "Ответ записан, переходим к следующему вопросу" << '\n' << std::endl;
		add_user_response(user_answer, i);
	}
}

void MathTest::add_user_response(int user_answer, int num_of_question) {
	_user_answers[num_of_question] = user_answer;
	if (_tasks[num_of_question]._answer == user_answer) {
		_user_answers_statuses[num_of_question] = true;
		_correct_user_answers_count += 1;
	}
	else _user_answers_statuses[num_of_question] = false;
}

void MathTest::show_statistics() {
	const int first_col_size = 11;
	const std::array<std::string, 4> first_col_names = {"Question", "True Answer", "Your Answer", "Result"};
	std::cout << "| " << std::setw(first_col_size) << std::right << "No" << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_wight) << std::right << i + 1 << ' ';
	}
	std::cout << '|' << std::endl;
	std::cout << '+' << std::setw(first_col_size + (_max_task_wight + 3) * _tasks_count + 3) << std::setfill('-') << '+' << std::setfill(' ') << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[0] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_wight) << std::right << parse_to_string(i) << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[1] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_wight) << std::right << _tasks[i]._answer << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[2] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_wight) << std::right << _user_answers[i] << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[3] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_wight) << std::right << ((_user_answers_statuses[i] == true) ? '+' : '-') << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "\n\nTotal Result : " << _correct_user_answers_count << " / " << _tasks_count << " (mark : ";
	float mark = (static_cast<float>(_correct_user_answers_count) / _tasks_count) * 100;
	if (mark > 90) { std::cout << "A"; }
	else if (mark >= 75) { std::cout << "B"; }
	else if (mark > 50) { std::cout << "C"; }
	else if (mark > 35) { std::cout << "D"; }
	else if (mark > 15) { std::cout << "E"; }
	else { std::cout << "F"; }
	std::cout << " )";
}

void MathTest::run() {
	assign_user_task();
	show_statistics();
}