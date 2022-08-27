#ifndef SRC_MULTISET_H_
#define SRC_MULTISET_H_

#include <iostream>

#include "set.h"

namespace STL {
template <typename Key>
class multiset : public set<Key> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = value_type const &;
  using size_type = size_t;
  using Node = typename set<key_type>::Node;

 public:
  using iterator = typename set<key_type>::iterator;
  using const_iterator = typename set<key_type>::const_iterator;

  multiset();
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset();
  multiset &operator=(multiset &&ms);

  iterator insert(const value_type &value);
  void merge(multiset &other);

  size_type count(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

 private:
  Node *insert_rec(Node *p, const value_type &k, iterator *it);
  size_type count_rec(const key_type &key, const Node *ptr);
};

template <typename key_type>
multiset<key_type>::multiset() : set<key_type>::set() {}

template <typename key_type>
multiset<key_type>::multiset(std::initializer_list<value_type> const &items) {
  for (auto &value : items) {
    insert(value);
  }
}

template <typename key_type>
multiset<key_type>::multiset(const multiset &ms) : multiset() {
  for (auto &value : ms) insert(value);
}

template <typename key_type>
multiset<key_type>::multiset(multiset &&ms) : set<key_type>::set(ms) {
  ms.size_ = 0;
}

template <typename key_type>
multiset<key_type>::~multiset() {
  this->clear();
}

template <typename key_type>
multiset<key_type> &multiset<key_type>::operator=(multiset<key_type> &&ms) {
  set<key_type> buf(ms);
  this->clear();
  this->swap(buf);
  return *this;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::insert(
    const value_type &value) {
  std::pair<iterator, bool> rez;
  rez.second = true;
  iterator *itrez = &rez.first;
  this->root_ = insert_rec(this->root_, value, itrez);
  this->size_++;
  return *itrez;
}

template <typename key_type>
typename multiset<key_type>::Node *multiset<key_type>::insert_rec(
    Node *p, const value_type &k, iterator *it) {
  if (!p) return it->get_current() = new Node(k);
  it->get_st().push(p);
  if (k < p->x)
    p->left = insert_rec(p->left, k, it);
  else
    p->right = insert_rec(p->right, k, it);
  return this->balance(p);
}

template <typename key_type>
void multiset<key_type>::merge(multiset<key_type> &other) {
  if (!other.empty()) {
    multiset<key_type> tmp(other);
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
      insert(*it);
      other.erase(it);
    }
  }
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type &key) {
  return count_rec(key, this->root_);
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::count_rec(
    const key_type &key, const Node *ptr) {
  if (ptr != nullptr) {
    return count_rec(key, ptr->left) + count_rec(key, ptr->right) +
           ((ptr->x == key) ? 1 : 0);
  } else {
    return 0;
  }
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type &key) {
  if (this->root_ == nullptr) throw std::out_of_range("Container is empty");
  iterator rez = this->begin();
  for (auto it = this->begin(); it != this->end(); ++it) {
    if (*it >= key && *it >= *rez) {
      rez = it;
      break;
    }
  }
  return rez;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type &key) {
  if (this->root_ == nullptr) throw std::out_of_range("Container is empty");
  iterator rez = this->begin();
  for (auto it = this->begin(); it != this->end(); ++it) {
    if (*it > key && *it >= *rez) {
      rez = it;
      break;
    }
  }
  return rez;
}

template <typename key_type>
typename std::pair<typename multiset<key_type>::iterator,
                   typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type &key) {
  return std::pair<iterator, iterator>(this->lower_bound(key),
                                       this->upper_bound(key));
}

template <typename key_type>
template <typename... Args>
typename std::pair<typename multiset<key_type>::iterator, bool>
multiset<key_type>::emplace(Args &&...args) {
  return std::make_pair(insert(key_type(args...)), true);
}

}  // namespace STL

#endif  // SRC_MULTISET_H_
