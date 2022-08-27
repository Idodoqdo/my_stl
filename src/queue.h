#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_
#include <iostream>

namespace STL {
template <typename T>
class queue {
 private:
  struct Node {
    T value;
    Node *next;
  };
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;

  size_type size_ = 0;
  Node *first, *last;
  void delete_queue();

 public:
  queue();
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  const_reference front() const { return first->value; }
  reference front() { return first->value; }
  const_reference back() const { return last->value; }
  reference back() { return last->value; }
  bool empty();
  size_type size() { return size_; }
  size_type size() const { return size_; }

  void push(const_reference value);
  void pop();
  void swap(queue &other);
  void emplace_back() {}
  template <typename value, typename... Args>
  void emplace_back(value val, Args &&...args);
};

template <typename value_type>
queue<value_type>::queue() {
  first = nullptr;
  last = nullptr;
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const &items)
    : first(nullptr), last(nullptr) {
  for (auto element : items) {
    push(element);
  }
}

template <typename value_type>
queue<value_type>::queue(const queue &q) : first(nullptr), last(nullptr) {
  delete_queue();
  Node *bbb = q.first;
  for (size_type i = 0; i < q.size(); ++i) {
    push(bbb->value);
    bbb = bbb->next;
  }
}

template <typename value_type>
queue<value_type>::queue(queue &&q) : first(nullptr), last(nullptr) {
  *this = std::move(q);
}

template <typename value_type>
queue<value_type> &queue<value_type>::operator=(queue &&q) {
  delete_queue();
  Node *bbb = q.first;
  for (size_type i = 0; i < q.size(); ++i) {
    push(bbb->value);
    bbb = bbb->next;
  }
  q.delete_queue();
  return *this;
}

template <typename value_type>
queue<value_type>::~queue() {
  delete_queue();
}

template <typename value_type>
void queue<value_type>::delete_queue() {
  while (first) {
    Node *buf = first;
    first = first->next;
    delete buf;
  }
  size_ = 0;
}

template <typename value_type>
bool queue<value_type>::empty() {
  bool empty = 1;
  if (first) {
    empty = 0;
  }
  return empty;
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  if (!first) {
    first = new Node{value, nullptr};
    last = first;
  } else {
    last->next = new Node();
    last = last->next;
    last->value = value;
    last->next = nullptr;
  }
  ++size_;
}

template <typename value_type>
void queue<value_type>::pop() {
  if (first) {
    Node *buf = first;
    first = first->next;
    delete buf;
    --size_;
  }
}

template <typename value_type>
void queue<value_type>::swap(queue &other) {
  queue<value_type> buf_queue = std::move(other);
  for (; first; pop()) {
    other.push(front());
  }
  for (; buf_queue.first; buf_queue.pop()) {
    push(buf_queue.front());
  }
}

template <typename value_type>
template <typename value_t, typename... Args>
void queue<value_type>::emplace_back(value_t value, Args &&...args) {
  push(value);
  emplace_back(args...);
}
}  // namespace STL

#endif  // SRC_QUEUE_H_
