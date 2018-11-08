//Это скрее всего не исправило ситуацию
//Наверное даже еще хуже получилось
//Но это самый простой способ заставить это все собираться
#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

//Я так понимаю проблема в настройках проектов, либо я чего-то не вижу

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_expression)
{
	ASSERT_NO_THROW(TPostfix p("2+4*(1/6)-8"));
}

TEST(TPostfix, can_create_postfix_form )
{
	TPostfix p("1+2/(3-3)");
	p.ToPostfix();

	EXPECT_EQ("1 2 3 3 - / + ",p.GetPostfix());
}

TEST(TPostfix, can_calculate)
{
	TPostfix p("1+2*(3-2)-4");
	p.ToPostfix();

	EXPECT_EQ(-1, p.Calculate());
}

TEST(TPostfix, can_not_divide_by_zero)
{
	TPostfix p("1+2/(3-3)");
	p.ToPostfix();

	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_not_create_postfix_with_wrong_brackets)
{
	TPostfix p("(((1+23)*1-22)+5)*2-(7");
	ASSERT_ANY_THROW(p.ToPostfix(););
}

TEST(TPostfix, can_mult_bracket_on_bracket)
{
	TPostfix p("(1+2/4/5-5)*(1-2)");
	p.ToPostfix();

	EXPECT_EQ(3.9, p.Calculate());
}

TEST(TPostfix, can_work_with_nested_brackets)
{
	TPostfix p("(1+(2+(3/3)))*(1-2)");
	p.ToPostfix();

	EXPECT_EQ(-4, p.Calculate());
}

TEST(TPostfix, can_not_calculate_expression_with_not_enough_opernands)
{
	TPostfix p("1++1");
	p.ToPostfix();

	ASSERT_ANY_THROW(p.Calculate());
}
