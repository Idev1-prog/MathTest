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