#pragma once
#include <cstdint>
#include <limits>

using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;

using F32 = float_t;
using F64 = double_t;


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