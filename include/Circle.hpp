#ifndef EMBEDDED_GFX_CIRCLE_HPP
#define EMBEDDED_GFX_CIRCLE_HPP

#include "Ellipse.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Circle : public Ellipse<CanvasT>
  {
    public:
      Circle(float x, float y, float r) : Ellipse<CanvasT>(x, y, r, r)
      {
      }
  };
}

#endif // EMBEDDED_GFX_CIRCLE_HPP