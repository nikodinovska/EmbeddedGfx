#ifndef EMBEDDED_GFX_CIRCLE_HPP
#define EMBEDDED_GFX_CIRCLE_HPP

#include "Ellipse.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing Circle.
   * 
   * @tparam CanvasT The type of the canvas.
   */
  template <typename CanvasT>
  class Circle : public Ellipse<CanvasT>
  {
    public:
      /**
       * @brief Construct a new Circle object.
       * 
       * @param x The x-coordinate of the center.
       * @param y The y-coordinate of the center.
       * @param r The radius of the circle.
       */
      Circle(float x = {}, float y = {}, float r = {})
        : Ellipse<CanvasT>(x, y, r, r)
      {
      }

      /**
       * @brief Construct a new Circle object
       * 
       * @param centerPoint The coordinates of the center.
       * @param r The radius of the circle.
       */
      Circle(const Vector2Df& centerPoint, float r)
        : Ellipse<CanvasT>(centerPoint, r, r)
      {
      }
  };
}

#endif // EMBEDDED_GFX_CIRCLE_HPP