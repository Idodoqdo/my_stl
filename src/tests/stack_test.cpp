#include "../stack.h"

#include <stack>

TEST(member_functions, defaul_stack) {
  STL::stack<int> test_stack;
  for (int i = 0; i < 10; i++) {
    test_stack.push(i);
  }
  EXPECT_EQ(10, test_stack.size());
  for (int i = 0; i < 10; i++) {
    test_stack.pop();
  }
  EXPECT_EQ(0, test_stack.size());
}

TEST(member_functions, initializer_list_constructor_stack) {
  STL::stack<int> test_stack_2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(test_stack_2.top(), i);
    test_stack_2.pop();
  }
}

TEST(member_functions, copy_constructor_stack) {
  STL::stack<int> test_stack;
  for (int i = 0; i < 10; i++) {
    test_stack.push(i);
  }
  STL::stack<int> test_stack_2 = test_stack;
  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(test_stack_2.top(), i);
    test_stack_2.pop();
  }
  EXPECT_EQ(10, test_stack.size());
}

TEST(member_functions, move_constructor_stack) {
  STL::stack<int> test_stack;
  for (int i = 0; i < 10; i++) {
    test_stack.push(i);
  }
  STL::stack<int> test_stack_2 = std::move(test_stack);
  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(test_stack_2.top(), i);
    test_stack_2.pop();
  }
  EXPECT_EQ(0, test_stack.size());
}

TEST(element_access, top_stack) {
  STL::stack<double> test_stack;
  test_stack.push(1.3);
  test_stack.push(2.3);
  test_stack.push(1.3);
  test_stack.top() += 2.0;
  STL::stack<double> origin;
  origin.push(1.3);
  origin.push(2.3);
  origin.push(1.3);
  origin.top() += 2.0;
  EXPECT_EQ(0, test_stack.empty());
  for (int i = 2; i > -1; i--) {
    EXPECT_DOUBLE_EQ(test_stack.top(), origin.top());
    test_stack.pop();
    origin.pop();
  }
  EXPECT_EQ(1, test_stack.empty());
}

TEST(modifiers, push_pop_swap_stack) {
  STL::stack<double> test_stack;
  test_stack.push(1.3);
  test_stack.push(2.3);
  test_stack.push(1.3);
  test_stack.top() += 2.0;
  STL::stack<double> test_stack_2;
  for (int i = 0; i < 10; i++) {
    test_stack_2.push(i + 0.37);
  }
  STL::stack<double> origin;
  origin.push(1.3);
  origin.push(2.3);
  origin.push(1.3);
  origin.top() += 2.0;
  STL::stack<double> origin_2;
  for (int i = 0; i < 10; i++) {
    origin_2.push(i + 0.37);
  }
  EXPECT_EQ(10, test_stack_2.size());
  EXPECT_EQ(3, test_stack.size());
  test_stack.swap(test_stack_2);
  origin.swap(origin_2);
  EXPECT_EQ(3, test_stack_2.size());
  EXPECT_EQ(10, test_stack.size());
  for (int i = 2; i > -1; i--) {
    EXPECT_DOUBLE_EQ(test_stack_2.top(), origin_2.top());
    test_stack_2.pop();
    origin_2.pop();
  }
  for (int i = 9; i > -1; i--) {
    EXPECT_DOUBLE_EQ(test_stack.top(), origin.top());
    test_stack.pop();
    origin.pop();
  }
}

TEST(bonus, emplace_stack) {
  STL::stack<int> test_stack;
  test_stack.push(1);
  test_stack.push(2);
  test_stack.push(3);
  test_stack.emplace_front(4, 5, 6);
  for (size_t i = 5; i == 0; i--, test_stack.pop()) {
    EXPECT_EQ(test_stack.top(), i + 1);
  }
}
