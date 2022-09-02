#ifndef EMBEDDED_GFX_SQUARE_HPP
#define EMBEDDED_GFX_SQUARE_HPP

#include "Rectangle.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Square : public Rectangle<CanvasT>
  {
    public:
      Square(float x, float y, float w) : Rectangle<CanvasT>{x, y, w, w}
      {
      }

  };
}


#endif // EMBEDDED_GFX_SQUARE_HPP