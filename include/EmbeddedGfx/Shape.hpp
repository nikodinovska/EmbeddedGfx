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
      using ColorT = typename CanvasT::ColorT;
    public:
      void setOutlineColor(const ColorT& color)
      {
        outlineColor_ = color;
      }
    protected:
      ColorT outlineColor_ = {};
  };
}


#endif //SHAPE_HPP