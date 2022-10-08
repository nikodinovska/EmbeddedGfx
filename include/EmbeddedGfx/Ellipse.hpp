#ifndef EMBEDDED_GFX_ELLIPSE_HPP
#define EMBEDDED_GFX_ELLIPSE_HPP

#include <cstddef>
#include <cmath>

#include "Vector2D.hpp"
#include "Shape.hpp"
#include "Line.hpp"

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
        if(this->fillColor_)
        {
          const size_t yLow = (centerPoint_.y - b_ > 0) ? std::roundf(centerPoint_.y - b_) : 0;
          const size_t yHigh = (centerPoint_.y + b_ <= canvas.getHeight() - 1) ? std::roundf(centerPoint_.y + b_) : canvas.getHeight() - 1;
          const size_t xLow = (centerPoint_.x - a_ > 0) ? std::roundf(centerPoint_.x - a_) : 0;
          const size_t xHigh = (centerPoint_.x + a_ <= canvas.getWidth() - 1) ? std::roundf(centerPoint_.x + a_) : canvas.getWidth() - 1;
          const size_t aSquared = std::roundf(a_ * a_);
          const size_t bSquared = std::roundf(b_ * b_);
          const auto centerRoundedFloat = centerPoint_.rounded();
          const Vector2D<size_t> centerRounded{
              static_cast<size_t>(centerRoundedFloat.x)
            , static_cast<size_t>(centerRoundedFloat.y)
          };
          for(size_t y = yLow; y <= yHigh; ++y)
          {
            const size_t yShifted = y - static_cast<size_t>(centerRounded.y);
            const size_t yShiftedSquared = yShifted * yShifted;
            for(size_t x = xLow; x <= xHigh; ++x)
            {
              const size_t xShifted = x - centerRounded.x;
              const size_t xShiftedSquared = xShifted * xShifted;
              if(this->fillColor_)
              {
                if(bSquared * xShiftedSquared + aSquared * yShiftedSquared < aSquared * bSquared)
                {
                  canvas.setPixel(x, y, *(this->fillColor_));
                }
              }
            }
          }
        }
        if(this->outlineColor_)
        {
          static constexpr float PI = 3.14159265358979323846f;
          static constexpr float deltaThetaDeg = 0.1f;  //< theta increment in degrees
          static constexpr float deltaTheta = deltaThetaDeg * PI / 180.0f;
          
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