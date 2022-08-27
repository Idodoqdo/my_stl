#ifndef SRC_ARRAY_H_
#define SRC_ARRAY_H_

#include <algorithm>
#include <iterator>

namespace STL {
template <class T, std::size_t N>
class array {
 private:
  T _arr[N];

 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = value_type const &;
  using iterator = T *;
  using const_iterator = iterator const;
  using size_type = std::size_t;

  array();
  explicit array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array &operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array &other);
  void fill(const_reference value);
};

template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("too many initializers for s21::array");
  }
  std::copy_n(items.begin(), size(), begin());
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy_n(a.begin(), a.size(), begin());
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  std::move(a.begin(), a.begin() + N, _arr);
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::move(a.begin(), a.begin() + N, _arr);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos > N) {
    throw std::out_of_range("array::at: __n (which is " + std::to_string(pos) +
                            ") >= _Nm (which is " + std::to_string(size()) +
                            ")");
  }
  return _arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return _arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return _arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return *(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return *(_arr + N - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(_arr + N - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return iterator(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return iterator(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return iterator(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return const_iterator(_arr);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return iterator(_arr + N);
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return const_iterator(_arr + N);
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return (size() == 0 ? true : false);
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  for (size_type i = 0; i < size(); ++i) {
    std::swap(_arr[i], other._arr[i]);
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size(); ++i) {
    _arr[i] = value;
  }
}

}  // namespace STL

#endif  // SRC_ARRAY_H_
