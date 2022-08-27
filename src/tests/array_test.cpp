#include "../array.h"

#include <array>

TEST(member_functions, defaul_array) {
  STL::array<int, 4> a;
  EXPECT_EQ(a.size(), 4);
}

TEST(member_functions, initializer_list_constructor_array) {
  STL::array<std::string, 2> a{"privet", "poka"};
  EXPECT_EQ(a[0], "privet");
  EXPECT_EQ(a[1], "poka");
}

TEST(member_functions, copy_constructor_array) {
  STL::array<int, 5> a{1, 2, 3, 4, 5};
  STL::array<int, 5> b(a);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(member_functions, move_constructor_array) {
  STL::array<std::string, 3> a{"a", "b", "c"};
  STL::array<std::string, 3> b(std::move(a));

  EXPECT_EQ(b[0], "a");
  EXPECT_EQ(b[1], "b");
  EXPECT_EQ(b[2], "c");
}

TEST(member_functions, assignment_operator_array) {
  STL::array<int, 5> a{11, 12, 13, 14, 15};
  STL::array<int, 5> b{0, 1, 2, 3, 4};

  a = std::move(b);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], i);
  }
}

TEST(element_access, at_array) {
  STL::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.at(2), a[2]);
}

TEST(element_access, front_array) {
  STL::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.front(), a[0]);
}

TEST(element_access, back_array) {
  STL::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.back(), a[(a.size() - 1)]);
}

TEST(element_access, data_array) {
  STL::array<int, 5> a{1, 2, 3, 4, 5};
  int* ptr = a.data();
  *ptr = 100;
  EXPECT_EQ(a[0], 100);
  ++ptr;
  *ptr = 99;
  EXPECT_EQ(a[1], 99);
  ptr[2] = 98;
  EXPECT_EQ(a[3], 98);
}

TEST(iterators, begin_array) {
  STL::array<std::string, 3> a{"hop", "hey", "lala"};
  EXPECT_EQ(*(a.begin()), a[0]);
}

TEST(iterators, end_array) {
  STL::array<std::string, 3> a{"hop", "hey", "lala"};
  EXPECT_EQ(*(a.end() - 1), a[(a.size() - 1)]);
}

TEST(capacity, empty_array) {
  STL::array<std::string, 0> a;
  STL::array<std::string, 3> b{"hop", "hey", "lala"};
  EXPECT_EQ(a.empty(), 1);
  EXPECT_EQ(b.empty(), 0);
}

TEST(capacity, size_array) {
  STL::array<std::string, 0> a;
  STL::array<std::string, 3> b{"hop", "hey", "lala"};
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.max_size(), 0);
  EXPECT_EQ(b.max_size(), 3);
}

TEST(modifiers, swap_array) {
  STL::array<int, 3> a{0, 1, 2};
  STL::array<int, 3> b{2, 1, 0};
  a.swap(b);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], a.size() - 1 - i);
    EXPECT_EQ(b[i], i);
  }
}

TEST(modifiers, fill_array) {
  STL::array<std::string, 3> a{"hop", "hey", "lala"};
  a.fill("kek");

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], "kek");
  }
}

TEST(modifiers, const_functions_array) {
  const STL::array<int, 5> a{1, 2, 3, 4, 5};

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
  EXPECT_EQ(*(a.begin()), 1);
  EXPECT_EQ(*(a.end() - 1), 5);
  int* ptr = a.data();
  *ptr = 100;
  EXPECT_EQ(a[0], 100);
}
