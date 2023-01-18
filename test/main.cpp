#include <iostream> 

#include "../include/Types.hpp"
#include "../include/Option.hpp"
#include "../include/Iter.hpp"

#include <limits>

template<typename T> 
struct Range {
  using Item = T;
  T cur;
  T end;

  Option<T> next() {
    return nth(0);
  }
  Option<T> nth(size_t n) {
    cur = saturating_add(cur, n)  
    return (cur < end) ? Some(cur) : None;
  }
};

template<typename T>
IterInterface<Range<T>> range(T upper, T lower) {
  return IterInterface<Range<T>> { 
    .impl = Range<T> { .cur = upper, .end = lower }
  };
}


template<typename T>
T saturating_add(T a, T b) {
  if (a > std::numeric_limits<T>::max() - b) {
    return std::numeric_limits<T>::max();
  }
  return a + b;
}
template<typename T>
T saturating_sub(T a, T b) {
  if (a < std::numeric_limits<T>::min() + b) {
    return std::numeric_limits<T>::min();
  } 
  return a - b;
}

int main() {



  return 0;
}