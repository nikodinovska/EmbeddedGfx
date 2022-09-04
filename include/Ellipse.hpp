#ifndef EMBEDDED_GFX_ELLIPSE_HPP
#define EMBEDDED_GFX_ELLIPSE_HPP

#include <cstddef>
#include <cmath>

#include "Vector2D.hpp"
#include "Shape.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Ellipse : public Shape<CanvasT>
  {
    public:
      Ellipse(float x, float y, float a, float b)
        : centerPoint_{x, y}
        , a_ (a)
        , b_ (b)
        {
        }

      void draw(CanvasT& canvas) const override
      {
        static constexpr float PI = 3.14159265358979323846f;
        static constexpr float deltaTheta = 0.1f * PI / 180.0f;
        Vector2D point(centerPoint_);
        float theta = 0.0f;
        while(theta < 2 * PI)
        {
          point.x = centerPoint_.x + a_ * std::cos(theta);
          point.y = centerPoint_.y + b_ * std::sin(theta);          
          canvas.setPixel(std::roundf(point.x), std::roundf(point.y));
          theta += deltaTheta;
        }
      }
    private:
      Vector2D centerPoint_;
      float a_, b_;
  };
}

#endif //EMBEDDED_GFX_ELLIPSE_HPP