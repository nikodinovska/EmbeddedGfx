#ifndef EMBEDDED_GFX_TRIANGLE_HPP
#define EMBEDDED_GFX_TRIANGLE_HPP

#include "Vector2D.hpp"
#include "Polygon.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing triangle shape.
   * 
   * @tparam CanvasT The type of the canvas.
   */
  template <typename CanvasT>
  class Triangle : public Polygon<3, CanvasT>
  {
    public:
      /**
       * @brief Construct a new Triangle object
       * 
       * @param points The points of the triangle.
       */
      Triangle(const std::array<Vector2Df, 3>& points)
        : Polygon<3, CanvasT>{points}
      {
      }

  };
}


#endif // EMBEDDED_GFX_TRIANGLE_HPP