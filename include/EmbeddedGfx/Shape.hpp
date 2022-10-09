#ifndef EMBEDDED_GFX_SHAPE_HPP
#define EMBEDDED_GFX_SHAPE_HPP

#include <optional>

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
      void setOutlineColor(const std::optional<ColorT>& color = std::nullopt)
      {
        outlineColor_ = color;
      }
      void setFillColor(const std::optional<ColorT>& color = std::nullopt)
      {
        fillColor_ = color;
      }
    protected:
      std::optional<ColorT> outlineColor_ = {};
      std::optional<ColorT> fillColor_ = {};
  };
}


#endif //EMBEDDED_GFX_SHAPE_HPP