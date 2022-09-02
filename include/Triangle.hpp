#ifndef EMBEDDED_GFX_TRIANGLE_HPP
#define EMBEDDED_GFX_TRIANGLE_HPP

#include "Vector2D.hpp"
#include "Polygon.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Triangle : public Polygon<3, CanvasT>
  {
    public:
      Triangle(const std::array<Vector2D, 3>& points) : Polygon<3, CanvasT>{points}
      {
      }

  };
}


#endif // EMBEDDED_GFX_TRIANGLE_HPP