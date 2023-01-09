#include <iostream> 

#include "../include/types.hpp"
#include "../include/option.hpp"
#include "../include/iter.hpp"

template<typename T> 
struct Slice {
  T* data;
  size_t len;

  struct Iter {
    using Item = T;
    T* ptr;
    T* end;

    Option<T> next() {
      return (ptr < end) ? Some(*ptr++) : None;
    }
  };

  template<template<typename> typename M = IterInterface>
  M<Iter> iter() {
    return M<Iter> { 
      .impl = Iter { .ptr = data, .end = data + len } 
    };
  }
};

template<typename T> 
struct Range {
  using Item = T;
  T cur;
  T end;

  Option<T> next() {
    return next(1);
  }
  Option<T> next(size_t n) {
    if (cur < end) {
      T out = cur;
      cur += n;
      return Some(out);
    }
    return None;
  }
};

template<typename T, template<typename> typename Interface = IterInterface>
Interface<Range<T>> range(T upper, T lower) {
  return Interface<Range<T>> { 
    .impl = Range<T> { .cur = upper, .end = lower }
  };
}

int main() {
  range(0, 100)
    .skip(10)
    .for_each([](auto x) {
      std::cout << x << std::endl;
    });

  return 0;
}