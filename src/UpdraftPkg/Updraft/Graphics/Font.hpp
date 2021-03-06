#pragma once

extern "C" {
#include <Uefi.h>
}

#include "../Utils/Types.hpp"
#include "Point.hpp"

class Font
{
  uint8 *m_data;

  uint8 m_height;

  uint8 getGlyphWidth(const char ch) const;

  uint8 *getGlyphDataPtr(const char ch) const;

  void drawGlyph(const char ch, const Point pos) const;

public:
  Font(CHAR16 *fileName);

  ~Font();

  void draw(const CHAR8 *str, const Point pos) const;
};
