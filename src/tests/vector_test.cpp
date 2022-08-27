#include "../vector.h"

#include <vector>

TEST(member_functions, defaul_vector) {
  STL::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(member_functions, parameterized_constructor_vector) {
  STL::vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
}

TEST(member_functions, initializer_list_constructor_vector) {
  std::vector<std::string> v1{"hop", "hey", "lala"};
  STL::vector<std::string> v2{"hop", "hey", "lala"};

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  auto v1_it = v1.begin();
  auto v2_it = v2.begin();
  for (; v1_it != v1.end(); ++v1_it, ++v2_it) {
    EXPECT_EQ(*v1_it, *v2_it);
  }
}

TEST(member_functions, copy_constructor_vector) {
  STL::vector<std::string> v1{"hop", "hey", "lala"};
  STL::vector<std::string> v2 = v1;

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  auto v1_it = v1.begin();
  auto v2_it = v2.begin();
  for (; v1_it != v1.end(); ++v1_it, ++v2_it) {
    EXPECT_EQ(*v1_it, *v2_it);
  }
}

TEST(member_functions, move_constructor_vector) {
  STL::vector<std::string> v1{"hop", "hey", "lala"};
  STL::vector<std::string> v2 = std::move(v1);

  std::vector<std::string> v3{"hop", "hey", "lala"};
  std::vector<std::string> v4 = std::move(v3);

  EXPECT_EQ(v1.size(), v3.size());
  EXPECT_EQ(v2.size(), v4.size());
  EXPECT_EQ(v1.capacity(), v3.capacity());
  EXPECT_EQ(v2.capacity(), v4.capacity());

  auto v2_it = v2.begin();
  auto v4_it = v4.begin();
  for (; v2_it != v2.end(); ++v2_it, ++v4_it) {
    EXPECT_EQ(*v2_it, *v4_it);
  }
}

TEST(member_functions, assignment_operator_vector) {
  STL::vector<int> v1{1, 2, 3, 4, 5};
  STL::vector<int> v2{1, 2, 3, 4, 5};
  v2 = std::move(v1);

  std::vector<int> v3{1, 2, 3, 4, 5};
  std::vector<int> v4{1, 2, 3, 4, 5};
  v4 = std::move(v3);

  EXPECT_EQ(v1.size(), v3.size());
  EXPECT_EQ(v2.size(), v4.size());
  EXPECT_EQ(v1.capacity(), v3.capacity());
  EXPECT_EQ(v2.capacity(), v4.capacity());

  auto v2_it = v2.begin();
  auto v4_it = v4.begin();
  for (; v2_it != v2.end(); ++v2_it, ++v4_it) {
    EXPECT_EQ(*v2_it, *v4_it);
  }
}

TEST(element_access, at_vector) {
  STL::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(2), v[2]);
}

TEST(element_access, front_vector) {
  STL::vector<std::string> v{"hop", "hey", "lala"};
  EXPECT_EQ(v.front(), v[0]);
}

TEST(element_access, back_vector) {
  STL::vector<std::string> v{"hop", "hey", "lala"};
  EXPECT_EQ(v.back(), v[v.size() - 1]);
}

TEST(element_access, data_vector) {
  STL::vector<int> v{1, 2, 3, 4, 5};
  int* ptr = v.data();
  *ptr = 100;
  EXPECT_EQ(v[0], 100);
  ++ptr;
  *ptr = 99;
  EXPECT_EQ(v[1], 99);
  ptr[2] = 98;
  EXPECT_EQ(v[3], 98);
}

TEST(iterators, begin_vector) {
  STL::vector<std::string> v{"hop", "hey", "lala"};
  STL::vector<std::string>::iterator it;
  it = v.begin();
  EXPECT_EQ(*it, v[0]);
}

TEST(iterators, end_vector) {
  STL::vector<std::string> v{"hop", "hey", "lala"};
  STL::vector<std::string>::iterator it;
  it = v.end();
  EXPECT_EQ(*(it - 1), v[v.size() - 1]);
}

TEST(capacity, reserve_vector) {
  STL::vector<std::string> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(capacity, capacity_vector) {
  STL::vector<int> v;
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(capacity, pop_back_vector) {
  STL::vector<int> v{1, 2, 3};
  v.pop_back();
  v.pop_back();
  v.pop_back();
  EXPECT_EQ(v.empty(), 1);
}

TEST(modifiers, clear_vector) {
  STL::vector<int> v{1, 2, 3};
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST(modifiers, insert_vector) {
  STL::vector<int> v{1, 2, 3};
  v.insert(v.begin() + 1, 999);
  EXPECT_EQ(v[1], 999);
  STL::vector<int> v2;
  v2.insert(v2.begin(), 666);
  EXPECT_EQ(v2[0], 666);
}

TEST(modifiers, erase_vector) {
  STL::vector<int> v1{1, 2, 3, 4, 5};
  int size = v1.size();
  v1.erase(v1.begin());
  EXPECT_EQ(v1.size(), size - 1);
  STL::vector<int> v2{2, 3, 4, 5};

  auto v1_it = v1.begin();
  auto v2_it = v2.begin();
  for (; v1_it != v1.end(); ++v1_it, ++v2_it) {
    EXPECT_EQ(*v1_it, *v2_it);
  }
}

TEST(modifiers, push_back_vector) {
  STL::vector<char> v1;
  v1.push_back('a');
  v1.push_back('b');
  v1.push_back('c');

  STL::vector<char> v2{'a', 'b', 'c'};

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(modifiers, const_functions_vector) {
  const STL::vector<int> v{1, 2, 3};

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
  EXPECT_EQ(*(v.cbegin()), 1);
  EXPECT_EQ(*(v.cend() - 1), 3);
  v.data();
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v.at(0), 1);
}

TEST(bonus, emplace_vector) {
  STL::vector<int> v{1, 2, 3};
  v.emplace(v.begin(), 0);

  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v.size(), 4);

  v.emplace_back(4);
  EXPECT_EQ(v[4], 4);
  EXPECT_EQ(v.size(), 5);
}
