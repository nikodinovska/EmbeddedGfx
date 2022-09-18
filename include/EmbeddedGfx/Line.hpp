#ifndef EMBEDDED_GFX_LINE_HPP
#define EMBEDDED_GFX_LINE_HPP

#include <cstddef>

#include "Drawable.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing Line.
   * 
   * @tparam CanvasT The type of the canvas.
   */
  template <typename CanvasT>
  class Line : public Drawable<CanvasT>
  {
    public:
      /**
       * @brief Construct a new Line object from the given coordinates.
       * 
       * @param x1 The x-coordinate of the start point.
       * @param y1 The y-coordinate of the start point.
       * @param x2 The x-coordinate of the end point.
       * @param y2 The y-coordinate of the end point.
       */
      Line(float x1 = {}, float y1 = {}, float x2 = {}, float y2 = {})
        : startPoint_{x1, y1}
        , endPoint_{x2, y2}
      {
      }

      /**
       * @brief Construct a new Line object from the given coordinates.
       * 
       * @param startPoint Vector holding the coordinates of the start point.
       * @param endPoint Vector holding the coordinates of the end point.
       */
      Line(const Vector2Df& startPoint, const Vector2Df& endPoint)
        : startPoint_ {startPoint}
        , endPoint_ {endPoint}
        {
        }

      /**
       * @brief Draw the line on the canvas.
       * 
       * @param canvas Reference to the canvas.
       */
      void draw(CanvasT& canvas) const override
      {
        Vector2Df k = (endPoint_ - startPoint_).unit();
        Vector2Df temp(startPoint_);
        Vector2Df tempRounded = temp.rounded();
        canvas.setPixel(tempRounded.x, tempRounded.y);
        while(tempRounded != endPoint_)
        {
          temp += k;
          tempRounded = temp.rounded();
          canvas.setPixel(tempRounded.x, tempRounded.y);
        }
        tempRounded = endPoint_.rounded();
        canvas.setPixel(tempRounded.x, tempRounded.y);
      }
    private:
      Vector2Df startPoint_;
      Vector2Df endPoint_;
  };
}


#endif //EMBEDDED_GFX_LINE_HPP