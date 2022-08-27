#include "../multiset.h"

#include <set>

TEST(member_functions, defaul_multiset) {
  STL::multiset<int> m;
  EXPECT_TRUE(m.empty());
}

TEST(member_functions, initializer_list_constructor_multiset) {
  STL::multiset<std::string> m1{"raz", "dva", "tri"};
  STL::multiset<std::string> m2{"raz", "dva", "tri"};

  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m2.size(), 3);

  auto m1_it = m1.begin();
  auto m2_it = m2.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m2_it) {
    EXPECT_EQ(*m1_it, *m2_it);
  }
}

TEST(member_functions, copy_constructor_multiset) {
  STL::multiset<std::string> m1{"raz", "dva", "tri"};
  STL::multiset<std::string> m2 = m1;

  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m2.size(), 3);

  auto m1_it = m1.begin();
  auto m2_it = m2.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m2_it) {
    EXPECT_EQ(*m1_it, *m2_it);
  }
}

TEST(member_functions, move_constructor_multiset) {
  STL::multiset<std::string> m1{"raz", "dva", "tri"};
  STL::multiset<std::string> m2(std::move(m1));

  STL::multiset<std::string> m3{"raz", "dva", "tri"};
  STL::multiset<std::string> m4 = std::move(m3);

  EXPECT_EQ(m1.size(), m3.size());
  EXPECT_EQ(m2.size(), m4.size());

  auto m2_it = m1.begin();
  auto m4_it = m2.begin();
  for (; m2_it != m2.end(); ++m2_it, ++m4_it) {
    EXPECT_EQ(*m2_it, *m4_it);
  }
}

TEST(capacity, empty_multiset) {
  STL::multiset<int> m{1, 2, 3, 4, 5};
  EXPECT_EQ(m.empty(), 0);
  m.clear();
  EXPECT_EQ(m.empty(), 1);
}

TEST(capacity, size_multiset) {
  STL::multiset<int> m{1, 2, 3, 4, 5};
  EXPECT_EQ(m.size(), 5);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(capacity, max_size_multiset) {
  STL::multiset<int> m1{1, 2, 3, 4, 5};
  STL::multiset<int> m2{1, 2, 3};
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(modifiers, clear_multiset) {
  STL::multiset<std::string> m1{"privet", "poka"};
  STL::multiset<std::string> m2{"lol", "olo", "lll", "ooo"};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(modifiers, insert_multiset) {
  STL::multiset<int> m;
  for (int i = 0; i < 5; ++i) {
    m.insert(i);
  }

  int i = 0;
  for (auto it = m.begin(); it != m.end(); ++it, ++i) {
    EXPECT_EQ(*it, i);
  }
}

TEST(modifiers, erase_multiset) {
  STL::multiset<int> m;
  for (int i = 0; i < 5; ++i) {
    m.insert(i);
  }

  m.erase(m.begin());

  int i = 1;
  for (auto it = m.begin(); it != m.end(); ++it, ++i) {
    EXPECT_EQ(*it, i);
  }
}

TEST(modifiers, swap_multiset) {
  STL::multiset<char> m1{'A', 'B', 'C'};
  STL::multiset<char> m2{'A', 'B', 'D', 'E'};

  std::multiset<char> m3{'A', 'B', 'C'};
  std::multiset<char> m4{'A', 'B', 'D', 'E'};

  m1.swap(m2);
  m3.swap(m4);

  auto m1_it = m1.begin();
  auto m3_it = m3.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m3_it) {
    EXPECT_EQ(*m1_it, *m3_it);
  }

  auto m2_it = m2.begin();
  auto m4_it = m4.begin();
  for (; m2_it != m2.end(); ++m2_it, ++m4_it) {
    EXPECT_EQ(*m2_it, *m4_it);
  }
}

TEST(modifiers, merge_multiset) {
  STL::multiset<char> m1{'A', 'B', 'C'};
  STL::multiset<char> m2{'A', 'B', 'D', 'E'};

  m1.merge(m2);

  std::multiset<char> m3{'A', 'B', 'C'};
  std::multiset<char> m4{'A', 'B', 'D', 'E'};

  m3.merge(m4);

  auto m1_it = m1.begin();
  auto m3_it = m3.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m3_it) {
    EXPECT_EQ(*m1_it, *m3_it);
  }

  EXPECT_EQ(m2.size(), m4.size());
}

TEST(lookup, count_multiset) {
  STL::multiset<int> m{1, 1, 1, 65, 9, 1, 1, 87, 65, 2, 65};

  EXPECT_EQ(m.count(1), 5);
  EXPECT_EQ(m.count(65), 3);
  EXPECT_EQ(m.count(0), 0);
}

TEST(lookup, find_multiset) {
  STL::multiset<int> m1{1, 2, 3, 4, 5};
  std::multiset<int> m2{1, 2, 3, 4, 5};

  EXPECT_EQ(*(m1.find(2)), *(m2.find(2)));
}

TEST(lookup, contains_multiset) {
  STL::multiset<int> m{1, 2, 3, 4, 5};

  EXPECT_EQ(m.contains(2), 1);
  EXPECT_EQ(m.contains(82), 0);
}

TEST(lookup, equal_range_multiset) {
  STL::multiset<int> m{1, 2, 3, 3, 3, 3, 4};
  auto range = m.equal_range(3);
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 3);
  }
}

TEST(lookup, lower_bound_multiset) {
  STL::multiset<int> m{11, 1, 1, 65, 9, 1, 1, 87, 65, 2, 65};
  EXPECT_EQ(*(m.lower_bound(9)), 9);
  EXPECT_EQ(*(m.lower_bound(4)), 9);
  EXPECT_EQ(*(m.lower_bound(12)), 65);
}

TEST(lookup, upper_bound_multiset) {
  STL::multiset<int> m{11, 1, 1, 65, 9, 1, 1, 87, 65, 2, 65};
  EXPECT_EQ(*(m.upper_bound(9)), 11);
  EXPECT_EQ(*(m.upper_bound(10)), 11);
  EXPECT_EQ(*(m.upper_bound(65)), 87);
}

TEST(bonus, emplace_multiset) {
  STL::multiset<double> m1;
  m1.emplace<double>(1.3);
  m1.emplace<double>(213.3);
  std::multiset<double> m2;
  m2.emplace<double>(1.3);
  m2.emplace<double>(213.3);
  EXPECT_EQ(m1.size(), m2.size());

  auto m1_it = m1.begin();
  auto m2_it = m2.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m2_it) {
    EXPECT_EQ(*m1_it, *m2_it);
  }
}
