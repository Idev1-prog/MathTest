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

TEST(MathTestTests, TwoParamConstructorTest) {
    MathTest obj(8, 5, 15);
    EXPECT_EQ(obj.get_tasks_count(), 8);
    std::vector<char> valid_opers = { '+', '-', '*', '/' };
    for (int i = 0; i < 8; i++) {
        auto it = std::find(valid_opers.begin(), valid_opers.end(),
            obj.get_tasks()[i]._oper);
        EXPECT_TRUE(it != valid_opers.end());
        EXPECT_GE(obj.get_tasks()[i]._num1, 5);
        EXPECT_LE(obj.get_tasks()[i]._num1, 15);
        EXPECT_GE(obj.get_tasks()[i]._num2, 5);
        EXPECT_LE(obj.get_tasks()[i]._num2, 15);
    }
}

TEST(MathTestTests, AddUserResponseCorrect) {
    MathTest obj(3, 10, 10, "+-+");
    obj.add_user_response(20, 0);  // верно
    EXPECT_EQ(obj.get_user_answer(0), 20);
    EXPECT_TRUE(obj.get_answer_status(0));
    EXPECT_EQ(obj.get_correct_count(), 1);
}

TEST(MathTestTests, AddUserResponseIncorrect) {
    MathTest obj(3, 10, 10, "+-+");
    obj.add_user_response(999, 1);  // неверно
    EXPECT_EQ(obj.get_user_answer(1), 999);
    EXPECT_FALSE(obj.get_answer_status(1));
    EXPECT_EQ(obj.get_correct_count(), 0);
}

TEST(MathTestTests, AddUserResponseMultiple) {
    MathTest obj(5, 10, 10, "++-*/");
    obj.add_user_response(20, 0);   // верно
    obj.add_user_response(20, 1);   // верно
    obj.add_user_response(5, 2);    // неверно
    obj.add_user_response(100, 3);  // верно
    obj.add_user_response(1, 4);    // верно

    EXPECT_EQ(obj.get_correct_count(), 4);
    EXPECT_TRUE(obj.get_answer_status(0));
    EXPECT_TRUE(obj.get_answer_status(1));
    EXPECT_FALSE(obj.get_answer_status(2));
    EXPECT_TRUE(obj.get_answer_status(3));
    EXPECT_TRUE(obj.get_answer_status(4));
}

TEST(MathTestTests, SingleTaskTest) {
    MathTest obj(1);
    EXPECT_EQ(obj.get_tasks_count(), 1);
    EXPECT_NE(obj.get_tasks(), nullptr);
}

TEST(MathTestTests, ZeroTaskTest) {
    EXPECT_ANY_THROW(MathTest obj(0));
}