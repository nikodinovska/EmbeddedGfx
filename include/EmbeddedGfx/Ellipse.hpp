#ifndef EMBEDDED_GFX_ELLIPSE_HPP
#define EMBEDDED_GFX_ELLIPSE_HPP

#include <cstddef>
#include <cmath>

#include "Vector2D.hpp"
#include "Shape.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing Ellipse.
   * 
   * @tparam CanvasT The type of the canvas.
   */
  template <typename CanvasT>
  class Ellipse : public Shape<CanvasT>
  {
    public:
      /**
       * @brief Construct a new Ellipse object.
       * 
       * @param x The x-coordinate of the center.
       * @param y The y-coordinate of the center.
       * @param a Half of the length of the major axis.
       * @param b Half of the length of the minor axis.
       */
      Ellipse(float x = {}, float y = {}, float a = {}, float b = {})
        : centerPoint_{x, y}
        , a_ (a)
        , b_ (b)
      {
      }

      /**
       * @brief Construct a new Ellipse object
       * 
       * @param centerPoint The coordinates of the center.
       * @param a Half of the length of the major axis.
       * @param b Half of the length of the minor axis.
       */
      Ellipse(const Vector2Df& centerPoint, float a, float b)
        : centerPoint_{centerPoint}
        , a_ (a)
        , b_ (b)
      {
      }

      /**
       * @brief Draw the ellipse on the canvas.
       * 
       * @param canvas Reference to the canvas.
       */
      void draw(CanvasT& canvas) const override
      {
        static constexpr float PI = 3.14159265358979323846f;
        static constexpr float deltaThetaDeg = 0.1f;  //< theta increment in degrees
        static constexpr float deltaTheta = deltaThetaDeg * PI / 180.0f;
        if(this->outlineColor_)
        {
          Vector2Df point{};
          Vector2Df pointRounded{};
          float theta = 0.0f;
          while(theta < 2 * PI)
          {
            point.x = centerPoint_.x + a_ * std::cos(theta);
            point.y = centerPoint_.y + b_ * std::sin(theta);
            pointRounded = point.rounded();
            canvas.setPixel(pointRounded.x, pointRounded.y, *(this->outlineColor_));
            theta += deltaTheta;
          }
        }
      }
    private:
      Vector2Df centerPoint_;
      float a_, b_;
  };
}

#endif //EMBEDDED_GFX_ELLIPSE_HPP