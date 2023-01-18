#pragma once
#include "Types.hpp"

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

  T& get_some() {
    return value;
  }
  const T& get_some() const {
    return value;
  }

  inline bool isSome() const {
    return has_value;
  }
  inline bool isNone() const {
    return !has_value;
  }

  template<typename Fn> 
    requires CanInvoke<Fn, T> 
  Option inspect_some(Fn fn) const {
    if(has_value) {
      std::invoke(fn, value);
    }
    return *this;
  }
  template<typename Fn> 
    requires CanInvoke<Fn, T> 
  Option inspect_none() const {
    if(has_value) {
      std::invoke<Fn, T>(fn);
    }
    return *this;
  }

  inline bool contains(T val) const {
    return has_value && value == val;
  }

  template<typename Fn> 
    requires CanInvoke<Fn, T>
  Option<Invoke<Fn, T>> map(Fn fn) const {
    return has_value ? Some(std::invoke(fn, value)) : None;
  }
  template<typename Pred>
    requires IsFn<bool, Pred, T> 
  Option<T> filter(Pred pred) const {
    return (has_value && pred(value)) ? Some(value) : None;
  }

  template<typename Fn> 
  Invoke<Fn, T> and_then(Fn fn) const {
    return has_value ? std::invoke<Fn, T>(fn, value) : None;
  }
  Option and_take(Option value) const {
    return has_value ? value : None;
  }
};

template<typename T> 
Option<T> Some(T value) {
  return Option<T>(value);
}