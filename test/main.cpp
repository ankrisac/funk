#include <iostream> 

#include "../include/types.hpp"
#include "../include/option.hpp"
#include "../include/iter.hpp"

template<typename T> 
struct Range {
  using Item = T;
  T cur;
  T end;

  Option<T> next() {
    return nth(0);
  }
  Option<T> nth(size_t n) {
    if (cur < end) {
      T out = cur;
      cur += n + 1;
      return Some(out);
    }
    return None;
  }
};

template<typename T>
IterInterface<Range<T>> range(T upper, T lower) {
  return IterInterface<Range<T>> { 
    .impl = Range<T> { .cur = upper, .end = lower }
  };
}

int main() {
  range(0, 100)
    .skip(10)
    .for_each([](auto x) { std::cout << x << std::endl; });

  return 0;
}