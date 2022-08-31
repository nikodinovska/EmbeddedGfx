#ifndef EMBEDDED_GFX_LINE_HPP
#define EMBEDDED_GFX_LINE_HPP

#include <cstddef>
#include <cmath>

#include "Shape.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Line : public Shape<CanvasT>
  {
    public:
      Line(float x1, float y1, float x2, float y2)
        : startPoint_{x1, y1}
        , endPoint_{x2, y2}
      {
      }

      void draw(CanvasT& canvas) const override
      {
        Vector2D dist = endPoint_ - startPoint_;
        Vector2D k = dist / dist.abs();
        Vector2D temp(startPoint_);
        canvas.setPixel(std::roundf(startPoint_.x), std::roundf(startPoint_.y));
        while(temp.rounded() != endPoint_)
        {
          temp += k;
          canvas.setPixel(std::roundf(temp.x), std::roundf(temp.y));
        }
        canvas.setPixel(std::roundf(endPoint_.x), std::roundf(endPoint_.y));
      }
    private:
      Vector2D startPoint_;
      Vector2D endPoint_;
  };
}


#endif //EMBEDDED_GFX_LINE_HPP