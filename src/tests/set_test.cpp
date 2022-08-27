#include "../set.h"

#include <set>

TEST(member_functions, defaulf_set) {
  STL::set<int> test;
  for (int i = 0; i < 5; i++) {
    test.insert(i);
  }
  ASSERT_EQ(5, test.size());
}

TEST(member_functions, initializer_list_constructor_set) {
  STL::set<int> test({0, 1, 2, 3, 4, 5, 6});
  ASSERT_EQ(7, test.size());
}

TEST(member_functions, copy_constructor_set) {
  STL::set<int> test({0, 1, 2, 3, 4, 5, 6});
  STL::set<int> test2(test);
  ASSERT_EQ(test2.size(), test.size());
}

TEST(member_functions, move_constructor_set) {
  STL::set<int> test({0, 1, 2, 3, 4, 5, 6});
  STL::set<int> test2(std::move(test));
  ASSERT_EQ(0, test.size());
  ASSERT_EQ(7, test2.size());
}

TEST(member_functions, assignment_operator_set) {
  STL::set<int> test({0, 1, 2, 3, 4, 5, 6});
  STL::set<int> test2;
  test2 = std::move(test);
  STL::set<int> test_0({0, 1, 2, 3, 4, 5, 6});
  STL::set<int> test_1;
  test_1 = std::move(test_0);
  ASSERT_EQ(test_0.size(), test.size());
  ASSERT_EQ(test_1.size(), test2.size());
}

TEST(capacity, size_set) {
  STL::set<int> test({0, 1, 2, 3, 4, 5, 6});
  ASSERT_EQ(7, test.size());
  std::set<int> test_0({0, 1, 2, 3, 4, 5, 6});
  ASSERT_EQ(7, test_0.size());
  STL::set<int> test2(std::move(test));
  ASSERT_EQ(0, test.size());
  ASSERT_EQ(7, test2.size());
  std::set<int> test_1(std::move(test_0));
  ASSERT_EQ(0, test_0.size());
  ASSERT_EQ(7, test_1.size());
}

TEST(capacity, empty_set) {
  STL::set<double> test({0.73, 1, 2.54});
  std::set<double> test_0({0.73, 1, 2.54});
  ASSERT_EQ(test_0.empty(), test.empty());
  STL::set<double> test2(std::move(test));
  std::set<double> test_1(std::move(test_0));
  ASSERT_EQ(test_0.empty(), test.empty());
}

TEST(modifiers, erase_set) {
  STL::set<double> test({0.73, 1});
  std::set<double> test_0({0.73, 1});
  test_0.erase(test_0.begin());
  test.erase(test.begin());
  ASSERT_EQ(test_0.size(), test.size());
}

TEST(modifiers, merge_set) {
  STL::set<double> test({0.73, 1});
  STL::set<double> test2({2.8, 5.4, 1.0987});
  std::set<double> test_0({0.73, 1});
  std::set<double> test_1({2.8, 5.4, 1.0987});
  ASSERT_EQ(test_0.size(), test.size());
  test_0.merge(test_1);
  test.merge(test2);
  ASSERT_EQ(test_0.size(), test.size());
}

TEST(modifiers, swap_set) {
  STL::set<double> test({0.73, 1});
  STL::set<double> test2({2.8, 5.4, 1.0987});
  std::set<double> test_0({0.73, 1});
  std::set<double> test_1({2.8, 5.4, 1.0987});
  ASSERT_EQ(test_0.size(), test.size());
  test_0.swap(test_1);
  test.swap(test2);
  ASSERT_EQ(test_0.size(), test.size());
  ASSERT_EQ(test_1.size(), test2.size());
}

TEST(modifiers, clear_set) {
  STL::set<double> test({1.2, 3, 0.73, 1});
  std::set<double> test_0({1.2, 3, 0.73, 1});
  ASSERT_EQ(test_0.size(), test.size());
  test_0.clear();
  test.clear();
  ASSERT_EQ(test_0.size(), test.size());
}

TEST(modifiers, insert_set) {
  STL::set<double> test;
  test.insert(1.2);
  test.insert(0.2);
  test.insert(0.38);
  test.insert(0.8);
  std::set<double> test_0;
  test_0.insert(1.2);
  test_0.insert(0.2);
  test_0.insert(0.38);
  test_0.insert(0.8);
  ASSERT_EQ(test_0.size(), test.size());
}

TEST(lookup, contains_set) {
  STL::set<double> test({1.2, 3, 0.73, 1});
  std::set<double> test_0({1.2, 3, 0.73, 1});
  ASSERT_EQ(test_0.size(), test.size());
  ASSERT_EQ(test.contains(3), 1);
}

TEST(lookup, find_set) {
  STL::set<float> test({1.2, 3, 0.73, 1});
  std::set<float> test_0({1.2, 3, 0.73, 1});
  ASSERT_EQ(*(test_0.find(3)), *(test.find(3)));
}

TEST(bonus, emplace_set) {
  STL::set<double> test;
  test.emplace(1.3);
  test.emplace(213.3);
  std::set<double> test_0;
  test_0.emplace(1.3);
  test_0.emplace(213.3);
  ASSERT_EQ(test.size(), test_0.size());
}
