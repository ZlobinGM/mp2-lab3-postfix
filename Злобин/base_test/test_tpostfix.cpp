#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_from_string)
{
	string s = "-10 +77";

	ASSERT_NO_THROW(TPostfix pf(s));
}

TEST(TPostfix, throw_when_first_operand_whiout_value)
{
	string s = "*99+  9 *88";
	TPostfix pf(s);

	ASSERT_ANY_THROW(pf.ToPostfix());
}

TEST(TPostfix, throw_when_last_operand_whiout_value)
{
	string s = "8*99+  9 *";
	TPostfix pf(s);

	ASSERT_ANY_THROW(pf.ToPostfix());
}

TEST(TPostfix, throw_when_brakets_dont_pair)
{
	string s = "(8*99+  (9 *88)";
	TPostfix pf(s);

	ASSERT_ANY_THROW(pf.ToPostfix());
}

TEST(TPostfix, throw_when_operand_after_operand)
{
	string s = "8*99+ - 9 *88";
	TPostfix pf(s);

	ASSERT_ANY_THROW(pf.ToPostfix());
}

TEST(TPostfix, can_erase_spaces_from_string)
{
	string spaces = "   a *  8     +   b    ";
	TPostfix pf(spaces);
	pf.ToPostfix();

	EXPECT_EQ("a * 8 + b ", pf.GetInfix());
}

TEST(TPostfix, can_topostfix_two_value)
{
	string s = "a+b";
	TPostfix pf(s);

	EXPECT_EQ("a b + ", pf.ToPostfix());
}

TEST(TPostfix, can_topostfix_many_values)
{
	string s = "a+b+c+d+e+f";
	TPostfix pf(s);

	EXPECT_EQ("a b + c + d + e + f + ", pf.ToPostfix());
}

TEST(TPostfix, can_topostfix_many_values_with_brackets)
{
	string s = "a+(b+c+(d+e)+f)";
	TPostfix pf(s);

	EXPECT_EQ("a b c + d e + + f + + ", pf.ToPostfix());
}

TEST(TPostfix, can_topostfix_value_and_const)
{
	string s = "a+2";
	TPostfix pf(s);

	EXPECT_EQ("a 2 + ", pf.ToPostfix());
}

TEST(TPostfix, can_topostfix_hard_example)
{
	string s = "(-10)  *  f  /a+   0 * 2   -11";
	TPostfix pf(s);

	EXPECT_EQ("0 10 - f * a / 0 2 * + 11 - ", pf.ToPostfix());
}

TEST(TPostfix, can_topostfix_variables_with_long_names)
{
	string s = "(-10)  *  function  /assimptota+   0 * 2   -11";
	TPostfix pf(s);

	EXPECT_EQ("0 10 - function * assimptota / 0 2 * + 11 - ", pf.ToPostfix());
}

TEST(TPostfix, can_calculate_two_const)
{
	string s = "6*6";
	TPostfix pf(s);
	pf.ToPostfix();
	pf.Calculate();

	EXPECT_DOUBLE_EQ(36., pf.Calculate());
}

TEST(TPostfix, throw_divide_by_zero)
{
	string s = "1/0";
	TPostfix pf(s);
	pf.ToPostfix();

	ASSERT_ANY_THROW(pf.Calculate());
}

TEST(TPostfix, can_calculate_with_brackets)
{
	string s = "122/(6/2+7)";
	TPostfix pf(s);
	pf.ToPostfix();
	pf.Calculate();

	EXPECT_DOUBLE_EQ(12.2, pf.Calculate());
}

TEST(TPostfix, can_calculate_hard_example)
{
	string s = "  (-10)  *  8  /10 + (  100 / 5 - 15) *2  ";
	TPostfix pf(s);
	pf.ToPostfix();

	EXPECT_DOUBLE_EQ(2., pf.Calculate());
}