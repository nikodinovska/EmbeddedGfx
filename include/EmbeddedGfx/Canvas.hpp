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
   * @tparam ColorType The color representation type.
   * @tparam DerivedCanvasT The type of the derived canvas.
   */
  template<size_t Width, size_t Height, CanvasType Type, typename ColorType, typename DerivedCanvasT>
  class Canvas
  {
    public:
      using ColorT = ColorType;
      using PixelT = typename ColorT::Type;
      static constexpr CanvasType canvasType = Type;
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

      /**
       * @brief Set the value of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param pixel The value of the pixel.
       */
      void setPixel(const size_t x, const size_t y, const ColorT& pixel)
      {
        (static_cast<DerivedCanvasT&>(*this)).setPixel(x, y, pixel);
      }

      /**
       * @brief Clear the canvas with a given color.
       * 
       * @param color The color to clear the canvas with.
       */
      void clear(const ColorT& color)
      {
        (static_cast<DerivedCanvasT&>(*this)).clear(color);
      }
  };
}

#endif //EMBEDDED_GFX_CANVAS_HPP