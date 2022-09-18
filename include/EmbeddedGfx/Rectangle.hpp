#ifndef EMBEDDED_GFX_RECTANGLE_HPP
#define EMBEDDED_GFX_RECTANGLE_HPP

#include "Polygon.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing rectangle shape.
   * 
   * @tparam CanvasT The type of the canvas.
   */
  template <typename CanvasT>
  class Rectangle : public Polygon<4, CanvasT>
  {
    public:
      /**
       * @brief Construct a new Rectangle object.
       * 
       * @param x The x-coordinate of the top-left point.
       * @param y The y-coordinate of the top-left point.
       * @param w The width of the rectangle.
       * @param h The height of the rectangle.
       */
      Rectangle(float x, float y, float w, float h)
        : Polygon<4, CanvasT>{{{{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}}}}
      {
      }

      /**
       * @brief Construct a new Rectangle object.
       * 
       * @param topLeftPoint The coordinates of the top-left point.
       * @param w The width of the rectangle.
       * @param h The height of the rectangle.
       */
      Rectangle(const Vector2Df& topLeftPoint, float w, float h)
        : Polygon<4, CanvasT>{{{topLeftPoint, topLeftPoint + Vector2Df{w, 0}
                              , topLeftPoint + Vector2Df{w, h}, topLeftPoint + Vector2Df{0, h}}}}
      {
      }
  };
}


#endif // EMBEDDED_GFX_RECTANGLE_HPP