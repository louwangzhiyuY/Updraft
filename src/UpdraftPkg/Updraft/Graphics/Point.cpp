#include "Point.hpp"

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../Graphics/Graphics.hpp"
#include "../Utils/Math.hpp"
#include "Screen.hpp"

double Point::distanceFrom(const Point pos) const
{
  return Math::Sqrt(Math::Square(pos.x - x) + Math::Square(pos.y - y));
}

void Point::draw(const Color color) const
{
  const uint32 width = Screen::Width(), height = Screen::Height();

  if (x < 0 || x >= static_cast<int32>(width) || y < 0 || y >= static_cast<int32>(height))
    return;

  auto *frameBufferBase = Graphics::BltBuffer();
  auto *pixel = frameBufferBase + (width * y) + x;

  const auto pixelFormat = Graphics::GraphicsOutputProtocol()->Mode->Info->PixelFormat;
  switch(pixelFormat) {
    case PixelBlueGreenRedReserved8BitPerColor:
      *pixel = {color.b, color.g, color.r, 0xff};
      break;
    case PixelRedGreenBlueReserved8BitPerColor:
      *pixel = {color.r, color.g, color.b, 0xff};
      break;
  }
}
