#include "../map.h"

#include <map>

TEST(member_functions, defaul_map) {
  STL::map<int, int> m;
  EXPECT_TRUE(m.empty());
}

TEST(member_functions, initializer_list_constructor_map) {
  STL::map<std::string, int> m1{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  std::map<std::string, int> m2{{"raz", 1}, {"dva", 2}, {"tri", 3}};

  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m2.size(), 3);

  EXPECT_EQ(m1["raz"], 1);
  EXPECT_EQ(m2["raz"], 1);

  EXPECT_EQ(m1["dva"], 2);
  EXPECT_EQ(m2["dva"], 2);

  EXPECT_EQ(m1["tri"], 3);
  EXPECT_EQ(m2["tri"], 3);
}

TEST(member_functions, copy_constructor_map) {
  STL::map<std::string, int> m1{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  STL::map<std::string, int> m2 = m1;

  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m2.size(), 3);

  auto m1_it = m1.begin();
  auto m2_it = m2.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m2_it) {
    EXPECT_EQ(*m1_it, *m2_it);
  }
}

TEST(member_functions, move_constructor_map) {
  STL::map<std::string, int> m1{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  STL::map<std::string, int> m2(std::move(m1));

  std::map<std::string, int> m3{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  std::map<std::string, int> m4 = std::move(m3);

  EXPECT_EQ(m1.size(), m3.size());
  EXPECT_EQ(m2.size(), m4.size());

  auto m2_it = m2.begin();
  auto m4_it = m4.begin();
  for (; m2_it != m2.end(); ++m2_it, ++m4_it) {
    EXPECT_EQ((*m2_it).first, (*m4_it).first);
    EXPECT_EQ((*m2_it).second, (*m4_it).second);
  }
}

TEST(element_access, at_map) {
  STL::map<std::string, int> m{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  EXPECT_EQ(m.at("raz"), 1);
  m.at("raz") = 10;
  EXPECT_EQ(m.at("raz"), 10);
}

TEST(element_access, operator_map) {
  STL::map<std::string, int> m{{"raz", 1}, {"dva", 2}, {"tri", 3}};
  EXPECT_EQ(m.at("raz"), 1);
  m["raz"] = 10;
  EXPECT_EQ(m.at("raz"), 10);
}

TEST(iterators, begin_map) {
  STL::map<int, int> m{{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ((*(m.begin())).first, 1);
}

TEST(iterators, end_map) {
  STL::map<int, int> m1{{1, 2}, {3, 4}};
  std::map<int, int> m2{{1, 2}, {3, 4}};

  auto m1_it = m1.begin();
  auto m2_it = m2.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m2_it) {
    EXPECT_EQ((*m1_it).first, (*m2_it).first);
  }
}

TEST(capacity, empty_map) {
  STL::map<int, int> m{{1, 2}, {3, 4}};
  EXPECT_EQ(m.empty(), 0);
  m.clear();
  EXPECT_EQ(m.empty(), 1);
}

TEST(capacity, size_map) {
  STL::map<int, int> m{{1, 2}, {3, 4}};
  EXPECT_EQ(m.size(), 2);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(modifiers, clear_map) {
  STL::map<std::string, int> m1{{"privet", 1}, {"poka", 2}};
  STL::map<std::string, int> m2{{"lol", 1}, {"olo", 2}, {"lll", 3}, {"ooo", 4}};

  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(modifiers, flag_insert_or_assign) {
  STL::map<int, int> m;
  std::map<int, int> m_og;

  m.insert_or_assign(3, 3);
  m_og.insert_or_assign(3, 3);
  m.insert_or_assign(3, 10);
  m_og.insert_or_assign(3, 10);

  m.insert_or_assign(4, 10);
  m_og.insert_or_assign(4, 10);

  EXPECT_EQ(m[3], m_og[3]);
  EXPECT_EQ(m[4], m_og[4]);
}

TEST(modifiers, erase_map) {
  STL::map<int, int> m{{1, 2}, {3, 4}};

  m.erase(m.begin());
  m.erase(m.begin());

  EXPECT_EQ(m.empty(), 1);
}

TEST(modifiers, swap_map) {
  STL::map<int, int> m1{{1, 2}, {3, 4}};
  STL::map<int, int> m2{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  std::map<int, int> m3{{1, 2}, {3, 4}};
  std::map<int, int> m4{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  m1.swap(m2);
  m3.swap(m4);

  auto m1_it = m1.begin();
  auto m3_it = m3.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m3_it) {
    EXPECT_EQ((*m1_it).first, (*m3_it).first);
  }

  auto m2_it = m2.begin();
  auto m4_it = m4.begin();
  for (; m2_it != m2.end(); ++m2_it, ++m4_it) {
    EXPECT_EQ((*m2_it).first, (*m4_it).first);
  }
}

TEST(modifiers, merge_map) {
  STL::map<int, int> m1{{1, 2}, {3, 4}};
  STL::map<int, int> m2{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  m1.merge(m2);

  std::map<int, int> m3{{1, 2}, {3, 4}};
  std::map<int, int> m4{{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  m3.merge(m4);

  auto m1_it = m1.begin();
  auto m3_it = m3.begin();
  for (; m1_it != m1.end(); ++m1_it, ++m3_it) {
    EXPECT_EQ((*m1_it).first, (*m3_it).first);
  }

  EXPECT_EQ(m2.size(), m4.size());
}

TEST(lookup, contains_map) {
  STL::map<int, int> m{{1, 2}, {3, 4}};

  EXPECT_EQ(m.contains(1), 1);
  EXPECT_EQ(m.contains(44), 0);
}

TEST(bonus, emplace_map) {
  STL::map<double, double> test;
  test.emplace(std::make_pair(3.3, 3.3));
  test.emplace(std::make_pair(14.5, 123.1));
  std::map<double, double> test_0;
  test_0.emplace(std::make_pair(3.3, 3.3));
  test_0.emplace(std::make_pair(14.5, 123.1));
  ASSERT_EQ(test.size(), test_0.size());
}
