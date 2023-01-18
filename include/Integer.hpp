#include "Types.hpp"


template<std::integral T>
struct Saturating {
  static constexpr T min = std::numeric_limits<T>::min();
  static constexpr T max = std::numeric_limits<T>::max(); 
 
  constexpr static T add(T a, T b) noexcept {
    return (a > max - b) ? max : (a + b);    
  }
  constexpr static T sub(T a, T b) noexcept {
    return (a < min + b) ? min : (a - b);
  }
};