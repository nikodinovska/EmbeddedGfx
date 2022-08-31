#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Drawable.hpp"

namespace EmbeddedGfx
{
  template <typename CanvasT>
  class Shape : public Drawable<CanvasT>
  {
    ///@todo add common shape attributes
    // scale, fill, rotation, other transformations
  };
}


#endif //SHAPE_HPP