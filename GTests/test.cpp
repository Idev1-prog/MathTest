#include "pch.h"
#include "math_test.h";

TEST(TaskTests, ConstructTest) {
	Task obj1;
	EXPECT_EQ(obj1._answer, obj1._num1 + obj1._num2);

	Task obj2(100, 200, '*');
	EXPECT_EQ(obj2._answer, obj2._num1 * obj2._num2);

	Task obj3(-30, 50, '/');
	EXPECT_EQ(obj3._answer, obj3._num1 / obj3._num2);

	Task obj4(50, 50, '+');
	EXPECT_EQ(obj4._answer, 100);
}

TEST(TaskTests, ExceptionsTest) {
	EXPECT_ANY_THROW(Task obj(30, 50, '8'););
}

TEST(MathTestTests, BaseContructorTest) {
	MathTest obj(5);
	EXPECT_EQ(obj.get_tasks_count(), 5);
	std::vector<char> opers = { '*', '-', '+', '/' };
	for (int i = 0; i < 5; i++) {
		auto target = std::find(opers.begin(), opers.end(), obj.get_tasks()[i]._oper);
		EXPECT_TRUE(target != opers.end());
	}
}

TEST(MathTestTests, AdvancedContructorTest) {
	char* opers = new char[5] {'+', '-', '*', '*', '/'};
	MathTest obj(5, 18, 20, opers);
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(obj.get_tasks()[i]._oper, opers[i]);
		EXPECT_TRUE(obj.get_tasks()[i]._num1 >= 18);
		EXPECT_TRUE(obj.get_tasks()[i]._num1 <= 20);
		EXPECT_TRUE(obj.get_tasks()[i]._num2 >= 18);
		EXPECT_TRUE(obj.get_tasks()[i]._num2 <= 20);
	}
}