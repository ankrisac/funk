#pragma once
#include "types.hpp"
#include "option.hpp"

template<typename It>
concept Iter = requires(It it, size_t n) {
  { it.next() } -> std::same_as<Option<typename It::Item>>;
  { it.nth(n) } -> std::same_as<Option<typename It::Item>>;
};


template<typename It>
struct DefaultImpl : public It {
  Option<typename It::Item> nth(size_t n) {
    for(size_t i = 1; i < n; i++) {
      if (static_cast<It>(this)->next().is_some()) break;
    }
    return static_cast<It>(this)->next();
  }
};


template<Iter It, typename Fn>
struct Map : DefaultImpl<Map<It, Fn>> {
  using Item = Invoke<Fn, typename It::Item>;
  
  It it;
  Fn fn;

  Option<Item> next() {
    return it.next().map(fn);
  }

  Option<Item> nth(size_t n) {
    return it.nth(n).map(fn);
  }
};

template<Iter It, typename Pred>
struct Filter : DefaultImpl<Filter<It, Pred>> {
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
};

template<Iter It>
struct Skip {
  using Item = typename It::Item;

  It it;

  size_t count;
  
  Option<Item> next() {
    if(count != 0) {
      it.nth(count);
      count = 0;
    }
    return it.next();
  }
  Option<Item> nth(size_t n) {
    if(count != 0) {
      it.nth(count);
      count = 0;
    }
    return it.nth(n);
  }
};

template<Iter It> 
struct Take {
  using Item = typename It::Item;

  It it;
  size_t remaining;

  Option<Item> next() {
    remaining 

    if (remaining > 0) {
      remaining--;
      return it.next();
    }
    return None;
  }
  Option<Item> nth(size_t n) {
    if (remaining > n) {
      remaining -= 
    }
    remaining = 0;
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
  Option<Item> nth(size_t n) {
    return impl.nth(n);
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