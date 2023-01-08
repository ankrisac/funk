#include <iostream> 


#include "../include/types.hpp"
#include "../include/option.hpp"



int main() {
  auto v = Some(32)
    .and_then([](auto x) { return Some(x * 2.0f); })
    .map([](auto x) { return x * 3.0f; })
    .if_some([](auto x) { 
      std::cout << x; 
    });

  std::cout << "Option[i32] : " << v << std::endl;
  
  return 0;
}