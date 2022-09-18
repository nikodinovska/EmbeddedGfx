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
    ///@todo add common shape attributes
    // scale, fill, rotation, other transformations
  };
}


#endif //SHAPE_HPP