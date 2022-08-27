#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <iostream>

namespace STL {
template <typename T>

class list {
 private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  class Node {
   public:
    Node *p_next;
    Node *p_prev;
    value_type data;
    Node(value_type data = value_type(), Node *p_next = nullptr,
         Node *p_prev = nullptr) {
      this->data = data;
      this->p_next = p_next;
      this->p_prev = p_prev;
    }
  };
  std::allocator<Node> n_;
  using node_manage = std::allocator_traits<std::allocator<Node>>;
  Node *phantom;
  Node *swap_sort(Node *ptr1, Node *ptr2);
  int Size;

 public:
  list();
  ~list();
  list(const list &l);
  list(list &&l);
  explicit list(std::initializer_list<value_type> const &items);
  explicit list(size_type n);

  class list_const_iterator;
  using const_iterator = list_const_iterator;
  class list_iterator {
   public:
    Node *it_;
    list_iterator() = default;
    explicit list_iterator(Node *value) : it_(value) {}
    reference operator*() { return it_->data; }
    void operator++() { it_ = it_->p_next; }
    void operator--() { it_ = it_->p_prev; }
    bool operator!=(list_iterator l) { return l.it_ != it_ ? true : false; }
    operator const_iterator() const { return const_iterator(it_); }
  };
  using iterator = list_iterator;
  iterator begin();
  iterator end();
  class list_const_iterator {
   public:
    const Node *it_;
    list_const_iterator() = default;
    explicit list_const_iterator(Node *value) : it_(value) {}
    const_reference operator*() { return it_->data; }
    void operator++() { it_ = it_->p_next; }
    void operator--() { it_ = it_->p_prev; }
    bool operator!=(list_const_iterator l) {
      return l.it_ != it_ ? true : false;
    }
    iterator nonconst() { return iterator(const_cast<Node *>(it_)); }
  };

  const_iterator begin() const;
  const_iterator end() const;
  const_reference front() { return phantom->p_next->data; }
  const_reference back() { return phantom->p_prev->data; }
  bool empty() { return (Size == 0) ? true : false; }
  size_type size() { return Size; }
  size_type max_size() const noexcept { return node_manage::max_size(n_); }

  void pop_front();
  void push_back(const_reference data);
  list &operator=(list &&l);
  void operator=(list &l);
  void clear();
  void push_front(const_reference data);
  void pop_back();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void swap(list &other);
  void reverce();
  void unique();
  void sort();
  void merge(list &other);
  void splice(const_iterator pos, list &other);

  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args);

  void emplace_back() {}
  template <typename value_t, typename... Args>
  void emplace_back(value_t value, Args &&...args);
  void emplace_front() {}
  template <typename value_t, typename... Args>
  void emplace_front(value_t value, Args &&...args);

 private:
  void insert_merge(iterator pos1, iterator &pos2);
};

template <typename value_type>
list<value_type>::list() {
  Size = 0;
  phantom = new Node;
  phantom->p_next = phantom;
  phantom->p_prev = phantom;
}

template <typename value_type>
list<value_type>::list(size_type n) : list() {
  for (unsigned i = 0; i < n; i++) {
    push_back(0);
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (auto element : items) {
    push_back(element);
  }
}

template <typename value_type>
list<value_type>::list(const list &l) : list() {
  Node *curren = l.phantom->p_next;
  while (curren != l.phantom) {
    push_back(curren->data);
    curren = curren->p_next;
  }
}

template <typename value_type>
list<value_type>::list(list &&l) : list() {
  if (this != &l) {
    this->swap(l);
  }
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(list &&l) {
  if (this != &l) {
    list(std::move(l)).swap(*this);
  }
  return *this;
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete phantom;
}
template <typename value_type>
void list<value_type>::push_back(const_reference data) {
  Node *current = new Node(data, phantom, phantom->p_prev);
  phantom->p_prev->p_next = current;
  phantom->p_prev = current;
  Size++;
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (Size > 0) {
    Node *temp = phantom->p_next;
    phantom->p_next = temp->p_next;
    temp->p_next->p_prev = phantom;
    delete temp;

    Size--;
  }
}

template <typename value_type>
void list<value_type>::clear() {
  while (Size) {
    pop_front();
  }
  phantom->p_next = phantom;
  phantom->p_prev = phantom;
}

template <typename value_type>
void list<value_type>::push_front(const_reference data) {
  Node *temp = phantom->p_next;
  phantom->p_next = new Node(data, temp, phantom);
  temp->p_prev = phantom->p_next;
  Size++;
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (Size > 0) {
    Node *temp = phantom->p_prev;
    phantom->p_prev = temp->p_prev;
    temp->p_prev->p_next = phantom;

    delete temp;

    Size--;
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  list<value_type>::iterator rez(phantom->p_next);
  return rez;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  list<value_type>::iterator rez(phantom);
  return rez;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  list<value_type>::const_iterator rez;
  rez.it_ = phantom->p_next;
  return rez;
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  list<value_type>::const_iterator rez;
  rez.it_ = phantom;
  return rez;
}

template <typename value_type>
void list<value_type>::operator=(list &l) {
  if (this != &l) {
    clear();
    Node *current = l.phantom->p_next;
    while (current != l.phantom) {
      push_back(current->data);
      current = current->p_next;
    }
    Size = l.Size;
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node *temp = pos.it_->p_prev;
  temp->p_next = new Node(value, pos.it_, temp);
  pos.it_->p_prev = temp->p_next;
  list::iterator rez(pos.it_->p_prev);

  Size++;
  return rez;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  pos.it_->p_prev->p_next = pos.it_->p_next;
  pos.it_->p_next->p_prev = pos.it_->p_prev;
  Size--;
  delete pos.it_;
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  if (this != &other) {
    int tempSize = Size;
    Size = other.Size;
    other.Size = tempSize;
    Node *tmp = phantom;
    phantom = other.phantom;
    other.phantom = tmp;
  }
}

template <typename value_type>
void list<value_type>::reverce() {
  list::iterator temp(phantom);
  do {
    Node *current = temp.it_->p_next;
    temp.it_->p_next = temp.it_->p_prev;
    temp.it_->p_prev = current;
    ++temp;
  } while (temp != end());
}

template <typename value_type>
void list<value_type>::unique() {
  list::iterator it;
  for (it = begin(); it != end(); ++it) {
    if (it.it_->data == it.it_->p_next->data) {
      list::iterator todel(it.it_->p_next);
      todel.it_ = it.it_->p_next;
      erase(todel);
      --it;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  Node *h;
  int i, j;
  for (i = 0; i < Size; i++) {
    h = phantom->p_next;
    int swapped = 0;
    for (j = 0; j < Size - 1; j++) {
      Node *p1 = h;
      Node *p2 = p1->p_next;
      if (p1->data > p2->data) {
        h = swap_sort(p1, p2);
        swapped = 1;
      }
      h = h->p_next;
    }
    if (swapped == 0) break;
  }
}

template <typename value_type>
typename list<value_type>::Node *list<value_type>::swap_sort(Node *ptr1,
                                                             Node *ptr2) {
  Node *temp = ptr2->p_next;
  ptr2->p_next->p_prev = ptr1;
  ptr1->p_prev->p_next = ptr2;
  ptr2->p_next = ptr1;
  ptr1->p_next = temp;
  temp = ptr1->p_prev;
  ptr1->p_prev = ptr2;
  ptr2->p_prev = temp;
  return ptr2;
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  if (&other != this) {
    list::iterator first(phantom->p_next), second(other.phantom->p_next);
    while (first != end() && second != other.end()) {
      if (first.it_->data < second.it_->data) {
        ++first;
      } else {
        insert_merge(first, second);
      }
    }
    while (second != other.end()) insert_merge(first, second);
    Size += other.Size;
    other.Size = 0;
  }
}

template <typename value_tupe>
void list<value_tupe>::insert_merge(iterator pos1, iterator &pos2) {
  auto temp = pos2.it_->p_next;
  pos2.it_->p_prev->p_next = temp;
  temp->p_prev = pos2.it_->p_prev;

  pos1.it_->p_prev->p_next = pos2.it_;
  pos2.it_->p_prev = pos1.it_->p_prev;

  pos2.it_->p_next = pos1.it_;
  pos1.it_->p_prev = pos2.it_;

  pos2.it_ = temp;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (this != &other) {
    iterator temp = pos.nonconst();
    temp.it_->p_prev->p_next = other.phantom->p_next;
    other.phantom->p_next->p_prev = temp.it_->p_prev;

    other.phantom->p_prev->p_next = temp.it_;
    temp.it_->p_prev = other.phantom->p_prev;
    other.phantom->p_next = other.phantom->p_prev = other.phantom;

    Size += other.Size;
    other.Size = 0;
  }
}

template <typename value_type>
template <typename value_t, typename... Args>
void list<value_type>::emplace_back(value_t value, Args &&...args) {
  push_back(value);
  emplace_back(args...);
}

template <typename value_type>
template <typename value_t, typename... Args>
void list<value_type>::emplace_front(value_t value, Args &&...args) {
  push_front(value);
  emplace_front(args...);
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::list_iterator list<value_type>::emplace(
    list<value_type>::iterator pos, Args &&...args) {
  auto it_ = insert(pos, value_type(args...));
  return it_;
}
}  // namespace STL

#endif  // SRC_LIST_H_
