#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include <iostream>
#include <iterator>

namespace STL {
template <class T, class Alloc = std::allocator<T>>
class vector {
 private:
  T* arr_;
  size_t size_;
  size_t capacity_;
  Alloc alloc_;

 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = T*;
  using const_iterator = iterator const;
  using size_type = std::size_t;

  vector() noexcept(noexcept(Alloc()));
  explicit vector(size_type n);
  explicit vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector& operator=(vector&& v);

  reference at(size_type pos);
  const_reference at(size_type n) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_cap);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const T& value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);
  template <typename... Args>
  void emplace_back(Args&&... args);

 private:
  void reallocate(size_type new_cap);
};

template <typename T, typename Alloc>
vector<T, Alloc>::vector() noexcept(noexcept(Alloc()))
    : alloc_(), capacity_(0), size_(0), arr_(nullptr) {}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n) : size_(n), capacity_(n) {
  arr_ = alloc_.allocate(capacity_);
  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(&arr_[i]);
  }
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(std::initializer_list<value_type> const& items)
    : capacity_(0), size_(0), arr_(nullptr) {
  arr_ = alloc_.allocate(items.size());
  size_ = capacity_ = items.size();

  for (size_type i = 0; i < items.size(); ++i) {
    alloc_.construct(&arr_[i], *(items.begin() + i));
  }
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector& v)
    : alloc_(v.alloc_), capacity_(v.capacity_), size_(v.size_) {
  arr_ = alloc_.allocate(capacity_);

  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(&arr_[i], v.arr_[i]);
  }
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector&& v)
    : alloc_(v.alloc_), capacity_(v.capacity_), size_(v.size_), arr_(nullptr) {
  swap(v);
  v.size_ = v.capacity_ = 0;
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector() {
  clear();
  alloc_.deallocate(arr_, capacity_);
}

template <typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& v) {
  size_ = v.size_;
  capacity_ = v.capacity_;

  reallocate(capacity_);

  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(&arr_[i], v.arr_[i]);
  }

  v.capacity_ = 0;
  v.size_ = 0;

  return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range(
        "vector::_M_range_check: __n (which is " + std::to_string(pos) +
        ") >= this->size() (which is " + std::to_string(size()) + ")");
  }
  return arr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range(
        "vector::_M_range_check: __n (which is " + std::to_string(pos) +
        ") >= this->size() (which is " + std::to_string(size()) + ")");
  }
  return arr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    size_type pos) {
  return arr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type pos) const {
  return arr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
  return *(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
  return *(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
  return *(arr_ + size_ - 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
  return *(arr_ + size_ - 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::data() noexcept {
  return iterator(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::data()
    const noexcept {
  return iterator(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept {
  return iterator(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin()
    const noexcept {
  return const_iterator(arr_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept {
  return iterator(arr_ + size_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend()
    const noexcept {
  return const_iterator(arr_ + size_);
}

template <typename T, typename Alloc>
bool vector<T, Alloc>::empty() const noexcept {
  return size() == 0;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const noexcept {
  return size_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size()
    const noexcept {
  return alloc_.max_size();
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (capacity_ < new_cap) {
    if (new_cap > max_size()) {
      throw std::length_error("vector::reserve");
    }
    reallocate(new_cap);
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reallocate(size_type new_cap) {
  T* new_arr = alloc_.allocate(new_cap);

  for (size_type i = 0; i < size_; ++i) {
    try {
      alloc_.construct(&new_arr[i], arr_[i]);

      alloc_.destroy(&arr_[i]);
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        alloc_.destroy(&new_arr[j]);
      }
      alloc_.deallocate(new_arr, new_cap);
      throw;
    }
  }

  alloc_.deallocate(arr_, capacity_);

  capacity_ = new_cap;
  arr_ = new_arr;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity()
    const noexcept {
  return capacity_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  reallocate(size_);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, const_reference value) {
  size_type index = pos - begin();
  if (empty())
    reserve(1);

  else if (!empty() && capacity_ == size_)
    reserve(size_ * 2);

  for (size_type i = size_, j = size_ - 1; i > 0; --i, --j) {
    if (i == index) {
      j++;
    } else {
      arr_[i] = arr_[j];
    }
  }
  arr_[index] = value;
  size_++;

  return iterator(arr_ + index);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::erase(iterator pos) {
  if (!empty()) {
    std::move(pos + 1, arr_ + size_, pos);
    --size_;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(const T& value) {
  if (size_ >= capacity_) {
    if (size_ == 0) {
      reserve(1);
    } else {
      reserve(capacity_ * 2);
    }
  }
  new (arr_ + size_) T(value);
  ++size_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
  if (size_) {
    --size_;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::swap(vector& other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(arr_, other.arr_);
}

template <typename T, typename Alloc>
template <typename... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(
    const_iterator pos, Args&&... args) {
  auto it = insert(pos, T(args...));
  return it;
}

template <typename T, typename Alloc>
template <typename... Args>
void vector<T, Alloc>::emplace_back(Args&&... args) {
  push_back(T(args...));
}

}  // namespace STL

#endif  // SRC_VECTOR_H_
