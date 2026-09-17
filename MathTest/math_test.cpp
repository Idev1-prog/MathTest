#include "math_test.h"

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

int calculate_with_operator(int num1, int num2, Operator op) {
	switch (op) {
	case Plus:
		return num1 + num2;
	case Minus:
		return num1 - num2;
	case Multiply:
		return num1 * num2;
	case Divide:
		return num1 / num2;
	default:
		throw std::invalid_argument("Invalid operation argument");
	}
}

Task::Task() {
	_num1 = generator(0, 200);
	_num2 = generator(0, 200);
	_oper = Operator(generator(0, 3));
	if (_oper == Divide && _num2 == 0) _num2 = 1;
	_answer = calculate_with_operator(_num1, _num2, _oper);
}

Task::Task(int min, int max) {
	_num1 = generator(min, max);
	_num2 = generator(min, max);
	_oper = Operator(generator(0, 3));
	if (_oper == Divide && _num2 == 0) _num2 = 1;
	_answer = calculate_with_operator(_num1, _num2, _oper);
}

Task::Task(int min, int max, Operator op) {
	_oper = op;
	_num1 = generator(min, max);
	_num2 = generator(min, max);
	if (op == Divide && _num2 == 0) _num2 = 1;
	_answer = calculate_with_operator(_num1, _num2, _oper);
}

char Task::get_char_oper() const noexcept {
	switch (_oper) {
	case Plus:
		return '+';
	case Minus:
		return '-' ;
	case Multiply:
		return '*';
	case Divide:
		return '/';
	}
}

void MathTest::calculate_max_task_width() noexcept {
	for (int i = 0; i < _tasks_count; i++) {
		std::string str_task = parse_to_string(i);
		if (str_task.size() > _max_task_width) _max_task_width = str_task.size();
	}
}

std::string MathTest::parse_to_string(int index) const noexcept {
	return std::to_string(_tasks[index]._num1) + _tasks[index].get_char_oper() + std::to_string(_tasks[index]._num2);
}

MathTest::MathTest(int tasks_count) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	if (tasks_count <= 0) throw std::invalid_argument("The number of tasks cannot be <= 0.");
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++){
		_tasks[i] = Task(0, 20, Operator(generator(0, 3)));
	}
	calculate_max_task_width();
}

MathTest::MathTest(int tasks_count, int min_num, int max_num) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	if (tasks_count <= 0) throw std::invalid_argument("The number of tasks cannot be <= 0.");
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++) {
		_tasks[i] = Task(min_num, max_num, Operator(generator(0, 3)));
	}
	calculate_max_task_width();
}

MathTest::MathTest(int tasks_count, int min_num, int max_num, const Operator* opers) : _tasks_count(tasks_count), _correct_user_answers_count(0), _user_answers_statuses(_tasks_count) {
	if (tasks_count <= 0) throw std::invalid_argument("The number of tasks cannot be <= 0.");
	_tasks = new Task[_tasks_count];
	_user_answers = new int[_tasks_count];
	for (int i = 0; i < tasks_count; i++) {
		_tasks[i] = Task(min_num, max_num, opers[i]);
	}
	calculate_max_task_width();
}

void MathTest::assign_user_task() {
	for (int i = 0; i < _tasks_count; i++) {
		int user_answer;
		std::cout << "Вопрос номер " << i + 1 << ": " << _tasks[i]._num1 << ' ' << _tasks[i].get_char_oper() << ' ' << _tasks[i]._num2 << std::endl;
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
		std::cout << "| " << std::setw(_max_task_width) << std::right << i + 1 << ' ';
	}
	std::cout << '|' << std::endl;
	std::cout << '+' << std::setw(first_col_size + (_max_task_width + 3) * _tasks_count + 3) << std::setfill('-') << '+' << std::setfill(' ') << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[0] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_width) << std::right << parse_to_string(i) << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[1] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_width) << std::right << _tasks[i]._answer << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[2] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_width) << std::right << _user_answers[i] << ' ';
	}
	std::cout << '|' << std::endl;

	std::cout << "| " << std::setw(first_col_size) << std::right << first_col_names[3] << ' ';
	for (int i = 0; i < _tasks_count; i++) {
		std::cout << "| " << std::setw(_max_task_width) << std::right << ((_user_answers_statuses[i] == true) ? '+' : '-') << ' ';
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