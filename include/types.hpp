#pragma once
#include <cstdint>

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;




#include <concepts>
#include <type_traits>

// Get return type of Fn(Args...)
template<typename Fn, typename... Args>
using Invoke = std::invoke_result_t<Fn, Args...>;

template<typename Return, typename Fn, typename... Args>
concept IsFn = requires (Fn fn, Args... args) {
  { fn(args...) } -> std::same_as<Return>;
};

template<typename Fn, typename... Args> 
concept CanInvoke = requires (Fn fn, Args... args) {
  { fn(args...) };
};