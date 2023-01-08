#pragma once
#include "types.hpp"

// Implicitly converts any Option<T>
constexpr struct OptionNone {} None;

template<typename T>
class Option {
  T value;
  bool has_value;
public:
  Option(OptionNone): has_value(false) {}
  Option(T some): value(some), has_value(true) {}

  friend std::ostream& operator<<(std::ostream& out, const Option& opt) {
    if (opt.has_value) {
      return out << "Some(" << opt.value << ")";  
    }    
    return out << "None";
  }

  inline bool is_some() {
    return has_value;
  }
  inline bool is_none() {
    return !has_value;
  }

  template<typename Fn> 
    requires CanInvoke<Fn, T> 
  Option if_some(Fn fn) {
    if(has_value) {
      std::invoke(fn, value);
    }
    return *this;
  }
  template<typename Fn> 
    requires CanInvoke<Fn, T> 
  Option if_none() {
    if(has_value) {
      std::invoke();
    }
    return *this;
  }

  inline bool contains(T val) {
    return has_value && value == val;
  }

  template<typename Fn> 
  Option<Invoke<Fn, T>> map(Fn fn) {
    return has_value ? Some(std::invoke(fn, value)) : None;
  }
  template<typename Pred>
    requires IsFn<bool, Pred, T> 
  Option<T> filter(Pred pred) {
    return (has_value && pred(value)) ? Some(value) : None;
  }

  template<typename Fn> 
  Invoke<Fn, T> and_then(Fn fn) {
    return has_value ? std::invoke(fn, value) : None;
  }
  Option and_take(Option value) {
    return has_value ? value : None;
  }
};

template<typename T> 
Option<T> Some(T value) {
  return Option<T>(value);
}