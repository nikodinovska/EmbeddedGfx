#ifndef EMBEDDED_GFX_RECTANGLE_HPP
#define EMBEDDED_GFX_RECTANGLE_HPP

#include "Polygon.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Rectangle : public Polygon<4, CanvasT>
  {
    public:
      Rectangle(float x, float y, float w, float h) : Polygon<4, CanvasT>{{{{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}}}}
      {
      }

  };
}


#endif // EMBEDDED_GFX_RECTANGLE_HPP