#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <iostream>

namespace STL {
template <typename T>
class stack {
 private:
  struct Node {
    T value;
    Node *next;
  };
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  Node *ptr_;
  size_type size_ = 0;

  void delete_stack();
  stack &operator=(const stack &s);
  void all_number(Node *bbb, T *buf_arr, const stack &s);

 public:
  stack();
  stack(const stack &s);
  stack(stack &&s);
  explicit stack(std::initializer_list<value_type> const &items);
  ~stack();

  void push(const_reference value);
  void pop();

  const_reference top() const { return ptr_->value; }
  reference top() { return ptr_->value; }
  bool empty();
  size_type size() const { return size_; }
  void swap(stack &other);

  void emplace_front() {}
  template <typename value_t, typename... Args>
  void emplace_front(value_t val, Args &&...args);
};

template <typename value_type>
stack<value_type>::stack() {
  ptr_ = nullptr;
}

template <typename value_type>
stack<value_type>::stack(const stack &s) : ptr_(nullptr) {
  *this = s;
}

template <typename value_type>
stack<value_type>::stack(stack &&s) : ptr_(nullptr) {
  delete_stack();
  *this = s;
  s.delete_stack();
}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : ptr_(nullptr) {
  for (auto element : items) {
    push(element);
  }
}

template <typename value_type>
stack<value_type>::~stack() {
  delete_stack();
}

template <typename value_type>
void stack<value_type>::delete_stack() {
  while (ptr_) {
    Node *buf = ptr_;
    ptr_ = ptr_->next;
    delete buf;
  }
  size_ = 0;
}

template <typename T>
void stack<T>::push(const_reference value) {
  if (ptr_) {
    Node *buf = new Node();
    buf->next = ptr_;
    buf->value = value;
    ptr_ = buf;
  } else {
    ptr_ = new Node();
    ptr_->value = value;
  }
  ++size_;
}

template <typename T>
void stack<T>::pop() {
  Node *buf = ptr_;
  if (ptr_) {
    ptr_ = ptr_->next;
    delete buf;
    --size_;
  }
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  stack<value_type> buf_stack = other;
  other = *this;
  *this = buf_stack;
}

template <typename value_type>
bool stack<value_type>::empty() {
  bool empty = 1;
  if (ptr_) {
    empty = 0;
  }
  return empty;
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(const stack &s) {
  delete_stack();
  Node *bbb = s.ptr_;
  value_type *buf_arr = new value_type[s.size()]();
  all_number(bbb, buf_arr, s);
  for (size_type j = s.size(); j > 0; --j) {
    push(buf_arr[j - 1]);
  }
  delete[] buf_arr;
  return *this;
}

template <typename value_type>
void stack<value_type>::all_number(Node *bbb, value_type *buf_arr,
                                   const stack &s) {
  for (size_type i = 0; i < s.size(); i++) {
    buf_arr[i] = bbb->value;
    bbb = bbb->next;
  }
}

template <typename value_type>
template <typename value_t, typename... Args>
void stack<value_type>::emplace_front(value_t value, Args &&...args) {
  push(value);
  emplace_front(args...);
}
}  // namespace STL

#endif  // SRC_STACK_H_
