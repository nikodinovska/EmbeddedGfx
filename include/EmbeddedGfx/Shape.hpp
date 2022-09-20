#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Drawable.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Interface for shape objects.
   * 
   * @tparam CanvasT Type of the canvas.
   */
  template <typename CanvasT>
  class Shape : public Drawable<CanvasT>
  {
    public:
      using PixelT = typename CanvasT::PixelT;
    public:
      void setOutlineColor(const PixelT& color)
      {
        outlineColor_ = color;
      }
    protected:
      PixelT outlineColor_ = {};
  };
}


#endif //SHAPE_HPP