#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throw_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_push)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.Push(4));
}

TEST(TStack, can_pop)
{
	TStack<int> st(5);
	st.Push(4);
	ASSERT_NO_THROW(st.Pop(););
}

TEST(TStack, can_not_pop_empty_stack)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Pop(););
}

TEST(TStack, can_not_push_full_stack)
{
	TStack<int> st(5);
	st.Push(2);
	st.Push(2);
	st.Push(2);
	st.Push(2);
	st.Push(2);
	ASSERT_ANY_THROW(st.Push(2));
}

TEST(TStack, can_push_and_pop)
{
	TStack<int> st(5);
	st.Push(2);
	EXPECT_EQ(2,st.Pop());
}


