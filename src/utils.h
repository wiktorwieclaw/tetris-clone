//
// Created by vixu on 1/7/21.
//

#ifndef SCRATCHTRIS_UTILS_H
#define SCRATCHTRIS_UTILS_H

#include <gxng_math.h>

#include <utility>

template <typename T>
concept Enum = std::is_enum_v<T>;

template <Enum T>
constexpr auto toUnderlying(T enumLiteral) {
  return static_cast<std::underlying_type_t<T>>(enumLiteral);
}

constexpr auto charToInt(char number) -> int { return number - '0'; }

constexpr auto intToChar(int number) -> char {
  return static_cast<signed char>('0' + number);
}

template <gxng::impl::Number T>
constexpr auto isInRange(T x, T start, T end) -> bool {
  return x >= start && x <= end;
}

#endif  // SCRATCHTRIS_UTILS_H
