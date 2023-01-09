#pragma once
#include "types.hpp"
#include "option.hpp"

template<typename It>
concept Iter = requires(It it, size_t n) {
  { it.next() } -> std::same_as<Option<typename It::Item>>;
  { it.next(n) } -> std::same_as<Option<typename It::Item>>;
};


template<typename It>
struct DefaultImpl : public {

  
  Option<Item> next() {
    return next(1);
  }
  Option<Item> next(size_t n) {

  }
};


template<Iter It, typename Fn>
struct Map : DefaultImpl<Item> {
  using Item = Invoke<Fn, typename It::Item>;
  
  It it;
  Fn fn;

  Option<Item> next(size_t n) {
    return it.next(n).map(fn);
  }
};

template<Iter It, typename Pred>
struct Filter {
  using Item = typename It::Item;
  
  It it;
  Pred pred;

  Option<Item> next() {
    while(true) {
      auto opt = it.next(); 
      if(opt.is_none()) return None;
      else if (pred(opt.get_some())) {
        return opt;
      }
    }
  }
  Option<Item> next(size_t n) {
    while(true) {
      auto opt = it.next(); 
      if(opt.is_none()) return None;
      else if (pred(opt.get_some())) {
        return opt;
      }
    }
  }
};

template<Iter It>
struct Skip {
  using Item = typename It::Item;

  It it;
  size_t count;
  
  Option<Item> next() {
    if(!skipped) {
      it.next(count);
      count = 0;
    }
    return it.next();
  }
};

template<Iter It> 
struct Take {
  using Item = typename It::Item;

  It it;
  size_t remaining;

  Option<Item> next() {
    if (remaining > 0) {
      remaining--;
      return it.next();
    }
    return None;
  }
};

template<Iter It>
struct IterInterface {
  using Item = typename It::Item;
  It impl;

  Option<Item> next() {
    return impl.next();
  }
  Option<Item> next(size_t n) {
    return impl.next(n);
  }

  template<typename Fn>
    requires CanInvoke<Fn, Item>
  IterInterface<Map<It, Fn>> map(Fn fn) {
    return { .impl = { .it = impl, .fn = fn } };
  }

  template<typename Pred>
    requires IsFn<bool, Pred, Item>
  IterInterface<Filter<It, Pred>> filter(Pred pred) {
    return { .impl = { .it = impl, .pred = pred } };
  }

  IterInterface<Skip<It>> skip(size_t n) {
    return { .impl = { .it = impl, .count = n } };
  }
  IterInterface<Take<It>> take(size_t n) {
    return { .impl = { .it = impl, .remaining = n } };
  }

  template<typename Fn>
    requires CanInvoke<Fn, Item>
  void for_each(Fn fn) {
    while(true) {
      auto opt = impl.next();
      opt.if_some(fn);
      if(opt.is_none()) break;
    }
  }
};