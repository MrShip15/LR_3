// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#ifndef  INCLUDE_SELFSHAREDPTR_HPP_
#define  INCLUDE_SELFSHAREDPTR_HPP_
#include <iostream>
#include <atomic>
#include <utility>

template <typename T>
class SelfSharedPtr {
 public:
  SelfSharedPtr();
  explicit SelfSharedPtr(T* ptr);
  SelfSharedPtr(const SelfSharedPtr& r);
  SelfSharedPtr(SelfSharedPtr&& r);
  ~SelfSharedPtr();

  auto operator=(const SelfSharedPtr& r) -> SelfSharedPtr&;
  auto operator=(SelfSharedPtr&& r) -> SelfSharedPtr&;

  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() const -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SelfSharedPtr& r);

  auto useCount() const -> size_t;

 private:
  T* object;
  std::atomic_uint *count_of_links;
};

template <typename T>
SelfSharedPtr<T>::SelfSharedPtr():object(nullptr), count_of_links(nullptr) {}

template <typename T>
SelfSharedPtr<T>::SelfSharedPtr(const SelfSharedPtr<T> &r):object(r.object){
  this->count_of_links = r.count_of_links;
  ++*count_of_links;
}

template <typename T>
SelfSharedPtr<T>::SelfSharedPtr(
    SelfSharedPtr<T> &&r):object(r.object),
                            count_of_links(r.count_of_links) {
  ++*count_of_links;
}

template <typename T>
SelfSharedPtr<T>::SelfSharedPtr(
    T *ptr):object(ptr),
              count_of_links(new std::atomic<uint>) {
  *count_of_links = 1;
}

template <typename T>
SelfSharedPtr<T>::~SelfSharedPtr<T>() {
  if (count_of_links) {
    if (*count_of_links == 1) {
      delete count_of_links;
      count_of_links = nullptr;
      object = nullptr;
    } else {
      --(*count_of_links);
    }
  }
}

template <typename T>
SelfSharedPtr<T>::operator bool() const {return get();}

template <typename T>
auto SelfSharedPtr<T>::operator*() const -> T & {
  if (this->object == nullptr){
    throw std::out_of_range("Object is empty!!!!");
  }
  return *object;
}

template <typename T>
auto SelfSharedPtr<T>::operator->() const -> T * {
  return object;
}

template <typename T>
auto SelfSharedPtr<T>::get() const -> T*{
  return object;
}

template <typename T>
void SelfSharedPtr<T>::reset() {
  if (count_of_links != nullptr) {
    object = nullptr;
    if (*count_of_links != 1) {
      --(*count_of_links);
    }else{
      delete count_of_links;
    }
    count_of_links = nullptr;
  }
}

template <typename T>
void SelfSharedPtr<T>::reset(T *ptr) {
  if (count_of_links != nullptr) {
    --(*count_of_links);
  }
  count_of_links = new std::atomic<uint>;
  *count_of_links = 1;
  object = ptr;
}

template <typename T>
auto SelfSharedPtr<T>::operator=(const SelfSharedPtr& r) -> SelfSharedPtr&{
  object = r.get();
  if (count_of_links != nullptr){
    --(*count_of_links);
  }
  count_of_links = r.count_of_links;
  ++(*count_of_links);
  return get();
}

template <typename T>
auto SelfSharedPtr<T>::operator=(SelfSharedPtr&& r) -> SelfSharedPtr& {
  object = std::move(r.object);
  if (this->count_of_links != nullptr){
    --(*count_of_links);
  }
  count_of_links = std::move(r.count_of_links);
  ++(*count_of_links);
  return get();
}

template <typename T>
void SelfSharedPtr<T>::swap(SelfSharedPtr<T> &r) {
  SelfSharedPtr tmp(r);
  r.object = object;
  r.count_of_links = count_of_links;
  object = std::move(tmp.object);
  count_of_links = std::move(tmp.count_of_links);
}

template <typename T>
auto SelfSharedPtr<T>::useCount() const -> size_t {
  return *count_of_links;
}

#endif  //  INCLUDE_SELFSHAREDPTR_HPP_
