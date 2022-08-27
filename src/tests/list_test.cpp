#include "../list.h"

#include <list>

TEST(member_functions, default_list) {
  STL::list<int> test;
  std::list<int> test_og;
  EXPECT_EQ(test.empty(), test_og.empty());
}

TEST(member_functions, initializer_list_constructor_list) {
  STL::list<int> test{1, 2, 3, 4, 5, 6, 7};
  std::list<int> test_og{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(test.empty(), test_og.empty());
  EXPECT_EQ(test.size(), test_og.size());
}

TEST(member_functions, copy_constructor_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  STL::list<int> test_2 = test;
  std::list<int> test_og2 = test_og;
  EXPECT_EQ(test.size(), test_2.size());
  EXPECT_EQ(test_og.size(), test_og2.size());
  auto i = test_2.begin();
  auto j = test_og2.begin();
  for (; i != test_2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(member_functions, move_constructor_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  STL::list<int> test_2 = std::move(test);
  std::list<int> test_og2 = std::move(test_og);
    EXPECT_NE(test.size(), test_2.size());
    EXPECT_NE(test_og.size(), test_og2.size());
  auto i = test_2.begin();
  auto j = test_og2.begin();
  for (; i != test_2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(member_functions, assignment_operator_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  STL::list<int> test_2;
  test_2 = std::move(test);
  std::list<int> test_og2;
  test_og2 = std::move(test_og);
  EXPECT_NE(test.size(), test_2.size());
  EXPECT_NE(test_og.size(), test_og2.size());
  auto i = test_2.begin();
  auto j = test_og2.begin();
  for (; i != test_2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(element_access, front_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  ASSERT_EQ(test.front(), test_og.front());
}

TEST(element_access, back_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  ASSERT_EQ(test.back(), test_og.back());
}

TEST(capacity, empty_list) {
  STL::list<int> test;
  std::list<int> test_og;
  EXPECT_EQ(test.empty(), test_og.empty());
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  EXPECT_EQ(test.empty(), test_og.empty());
}

TEST(capacity, size_list) {
  STL::list<int> test;
  std::list<int> test_og;
  EXPECT_EQ(test.size(), test_og.size());
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  EXPECT_EQ(test.size(), test_og.size());
}

TEST(modifiers, clear_list) {
  STL::list<int> test;
  std::list<int> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i);
    test_og.push_front(i);
  }
  EXPECT_EQ(test.size(), test_og.size());
  EXPECT_EQ(test.empty(), test_og.empty());
  test.clear();
  test_og.clear();
  EXPECT_EQ(test.size(), test_og.size());
  EXPECT_EQ(test.empty(), test_og.empty());
}

TEST(modifiers, insert_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  auto i = test.begin();
  auto j = test_og.begin();
  test.insert(test.begin(), 2.345);
  test_og.insert(test_og.begin(), 2.345);
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, erase_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  auto elem_1 = test.begin();
  auto elem_2 = test_og.begin();
  ++elem_1;
  ++elem_2;
  test.erase(elem_1);
  test_og.erase(elem_2);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, push_back_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_back(i + 0.37);
    test_og.push_back(i + 0.37);
  }
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, pop_back_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  test.pop_back();
  test_og.pop_back();
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, pop_front_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_back(i + 0.37);
    test_og.push_back(i + 0.37);
  }
  test.pop_front();
  test_og.pop_front();
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, swap_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  STL::list<double> test_2;
  std::list<double> test_og2;
  for (auto i = 0; i < 5; ++i) {
    test.push_back(i + 0.7);
    test_og.push_back(i + 0.7);
  }
  test.swap(test_2);
  test_og.swap(test_og2);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
  auto i_2 = test_2.begin();
  auto j_2 = test_og2.begin();
  for (; i_2 != test_2.end(); ++i_2, ++j_2) {
    EXPECT_EQ(*i_2, *j_2);
  }
}

TEST(modifiers, merge_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  STL::list<double> test_2;
  std::list<double> test_og2;
  for (auto i = 0; i < 5; ++i) {
    test.push_back(i + 0.7);
    test_og.push_back(i + 0.7);
  }
  test.merge(test_2);
  test_og.merge(test_og2);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, splice_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  STL::list<double> test_2;
  std::list<double> test_og2;
  for (auto i = 0; i < 5; ++i) {
    test.push_back(i + 0.7);
    test_og.push_back(i + 0.7);
  }
  auto elem_1 = test.begin();
  auto elem_2 = test_og.begin();
  ++elem_1;
  ++elem_2;
  test.splice(elem_1, test_2);
  test_og.splice(elem_2, test_og2);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, reverse_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }

  test.reverce();
  test_og.reverse();
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, unique_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }

  test.unique();
  test_og.unique();
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(modifiers, sort_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }

  test.sort();
  test_og.sort();
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(bonus, emplace_back) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  test.emplace_back(1);
  test_og.emplace_back(1);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(bonus, emplace_front_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  test.emplace_front(1);
  test_og.emplace_front(1);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(bonus, emplace_list) {
  STL::list<double> test;
  std::list<double> test_og;
  for (auto i = 0; i < 10; ++i) {
    test.push_front(i + 0.37);
    test_og.push_front(i + 0.37);
  }
  test.emplace(test.begin(), 1);
  test_og.emplace(test_og.begin(), 1);
  auto i = test.begin();
  auto j = test_og.begin();
  for (; i != test.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}
