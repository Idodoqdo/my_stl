#include "../queue.h"

#include <queue>

TEST(member_functions, defaul_queue) {
  STL::queue<int> test_queue;
  for (int i = 0; i < 10; i++) {
    test_queue.push(i);
  }
  EXPECT_EQ(10, test_queue.size());
  for (int i = 0; i < 10; i++) {
    test_queue.pop();
  }
  EXPECT_EQ(0, test_queue.size());
}

TEST(member_functions, copy_constructor_queue) {
  STL::queue<int> test_queue;
  for (int i = 0; i < 10; i++) {
    test_queue.push(i);
  }
  STL::queue<int> test_queue_2 = test_queue;
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(test_queue_2.front(), i);
    test_queue_2.pop();
  }
  EXPECT_EQ(10, test_queue.size());
}

TEST(member_functions, initializer_list_constructor_queue) {
  STL::queue<int> test_queue_2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::queue<int> origin({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(test_queue_2.front(), origin.front());
    test_queue_2.pop();
    origin.pop();
  }
}

TEST(member_functions, move_constructor_queue) {
  STL::queue<int> test_queue;
  for (int i = 0; i < 10; i++) {
    test_queue.push(i);
  }
  std::queue<int> origin;
  for (int i = 0; i < 10; i++) {
    origin.push(i);
  }
  STL::queue<int> test_queue_2 = std::move(test_queue);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(test_queue_2.front(), origin.front());
    test_queue_2.pop();
    origin.pop();
  }
  EXPECT_EQ(0, test_queue.size());
}

TEST(element_access, front_back_and_empty_queue) {
  STL::queue<double> test_queue;
  test_queue.push(1.3);
  test_queue.push(4.3);
  test_queue.push(3.3);
  test_queue.front() += 2.0;
  test_queue.back() += 2.0;
  EXPECT_EQ(0, test_queue.empty());
  std::queue<double> origin;
  origin.push(1.3);
  origin.push(4.3);
  origin.push(3.3);
  origin.front() += 2.0;
  origin.back() += 2.0;
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(test_queue.front(), origin.front());
    test_queue.pop();
    origin.pop();
  }
  EXPECT_EQ(1, test_queue.empty());
}

TEST(modifiers, swap_queue) {
  STL::queue<double> test_queue;
  test_queue.push(1.3);
  test_queue.push(2.3);
  test_queue.push(1.3);
  test_queue.back() += 2.0;
  STL::queue<double> test_queue_2;
  for (int i = 0; i < 10; i++) {
    test_queue_2.push(i + 0.37);
  }
  std::queue<double> origin;
  origin.push(1.3);
  origin.push(2.3);
  origin.push(1.3);
  origin.back() += 2.0;
  std::queue<double> origin_2;
  for (int i = 0; i < 10; i++) {
    origin_2.push(i + 0.37);
  }
  EXPECT_EQ(10, test_queue_2.size());
  EXPECT_EQ(3, test_queue.size());
  test_queue.swap(test_queue_2);
  origin.swap(origin_2);
  EXPECT_EQ(3, test_queue_2.size());
  EXPECT_EQ(10, test_queue.size());
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(test_queue_2.front(), origin_2.front());
    test_queue_2.pop();
    origin_2.pop();
  }
  for (int i = 0; i < 10; i++) {
    EXPECT_DOUBLE_EQ(test_queue.front(), origin.front());
    test_queue.pop();
    origin.pop();
  }
}

TEST(bonus, emplace_queue) {
  STL::queue<int> test_queue;
  test_queue.push(1);
  test_queue.push(2);
  test_queue.push(3);
  test_queue.emplace_back<int>(4, 5, 6);
  for (size_t i = 0; i < 6; i++, test_queue.pop()) {
    EXPECT_EQ(test_queue.front(), i + 1);
  }
}
