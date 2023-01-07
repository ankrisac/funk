#include <iostream> 


#include "../include/types.hpp"
#include "../include/option.hpp"



int main() {
  Option<i32> value = Some(32);

  auto v = value
    .and_then([](auto x) { return Some(x * 2.0f); })
    .map([](auto x) { return x * 3.0f; });

  std::cout << "Option[i32] : " << v << std::endl;
  
  return 0;
}