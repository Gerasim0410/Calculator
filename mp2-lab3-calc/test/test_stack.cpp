#include "../include/stack.h"

#include <gtest.h>

#ifndef USE_SET

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> st;
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> st1;
	TStack<int> st2;

	st1.Push(1);
	st2.Push(1);
	EXPECT_FALSE(&st1 == &st2);
}

TEST(TStack, created_stack_is_empty)
{
	TStack<int> st;
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, can_push_element)
{
	TStack<int> st;
	st.Push(5);
	EXPECT_EQ(false, st.IsEmpty());
}

TEST(TStack, can_pop_element)
{
	TStack<int> st;
	st.Push(5);
	EXPECT_EQ(5, st.Pop());
}

TEST(TStack, throws_when_pop_empty) {
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}

#else

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cannot_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cannot_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> st1(5);
	TStack<int> st2(5);

	st1.Push(1);
	st2.Push(1);
	EXPECT_FALSE(&st1 == &st2);
}

TEST(TStack, created_stack_is_empty)
{
	TStack<int> st(5);
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, can_push_element)
{
	TStack<int> st(5);
	st.Push(5);
	EXPECT_EQ(false, st.IsEmpty());
}

TEST(TStack, can_pop_element)
{
	TStack<int> st(5);
	st.Push(5);
	EXPECT_EQ(5, st.Pop());
}

TEST(TStack, throws_when_pop_empty) {
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Pop());
}

#endif