#pragma once

#include "../Utils/Types.hpp"

struct Color {
  uint8 r, g, b;

  constexpr Color() = default;

  constexpr Color(const uint8 _r, const uint8 _g, const uint8 _b)
    : r(_r), g(_g), b(_b)
  { }
};
