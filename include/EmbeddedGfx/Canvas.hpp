#ifndef EMBEDDED_GFX_CANVAS_HPP
#define EMBEDDED_GFX_CANVAS_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>

#include "Colors.hpp"
#include "Drawable.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  /**
   * Canvas types based on the matrix buffer
   * representation.
   * 
   */
  enum class CanvasType
  {
    Normal,
    Page
  };

  /**
   * @brief Base CRTP class for canvas.
   * 
   * @tparam Width The width of the canvas in pixels.
   * @tparam Height The height of the canvas in pixels.
   * @tparam Type The type of the canvas.
   * @tparam ColorT The color representation type.
   */
  template<size_t Width, size_t Height, CanvasType Type, ColorType ColorRep, typename DerivedCanvasT>
  class Canvas
  {
    public:
      using ColorT = std::conditional_t<
                      ColorRep == ColorType::BlackAndWhite
                    , BlackandWhite
                    , std::conditional_t<
                        ColorRep == ColorType::RGB565
                      , RGB565
                      , std::conditional_t<
                            ColorRep == ColorType::RGB666
                          , RGB666
                          , RGB888
                        >
                      >
                    >;
      using PixelT = typename ColorT::Type;
      static constexpr CanvasType canvasType = Type;
      static constexpr ColorType colorType = ColorRep;
      using DrawableT = Drawable<DerivedCanvasT>;
    public:
      /**
       * @brief Get the height of the canvas which is
       * actually the number of rows.
       * 
       * @return size_t The height of the canvas.
       */
      size_t getHeight() const
      {
        return Height;
      }

      /**
       * @brief Get the width of the canvas which is
       * actually the number of columns.
       * 
       * @return size_t The width of the canvas.
       */
      size_t getWidth() const
      {
        return Width;
      }

      /**
       * @brief Draw object on the canvas.
       * 
       * @param drawable Reference to drawable object.
       */
      void draw(const DrawableT& drawable)
      {
        drawable.draw(static_cast<DerivedCanvasT&>(*this));
      }

      void setPixel(const size_t x, const size_t y, const ColorT& value)
      {
        (static_cast<DerivedCanvasT&>(*this)).setPixel(x, y, value);
      }
  };
}

#endif //EMBEDDED_GFX_CANVAS_HPP