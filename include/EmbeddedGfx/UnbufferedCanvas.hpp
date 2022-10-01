#ifndef EMBEDDED_GFX_UNBUFFERED_CANVAS_HPP
#define EMBEDDED_GFX_UNBUFFERED_CANVAS_HPP

#include "Canvas.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class represnting canvas with buffer in memory.
   * 
   * @tparam Width The width of the canvas in pixels.
   * @tparam Height The height of the canvas in pixels.
   * @tparam Type The type of the canvas.
   * @tparam ColorType The color representation type.
   * @tparam DisplayT The type for the display device.
   * @note DisplayT must have method setPixel(x, y, value).
   */
  template<size_t Width, size_t Height, CanvasType Type, typename ColorType, typename DisplayT>
  class UnbufferedCanvas
    : public Canvas<Width, Height, Type, ColorType
                  , UnbufferedCanvas<Width, Height, Type, ColorType, DisplayT>>
  {
    using BaseT = Canvas<Width, Height, Type, ColorType, UnbufferedCanvas>;
    public:
      using ColorT = typename BaseT::ColorT;
      using PixelT = typename BaseT::PixelT;
      static constexpr uint8_t PageSize = 8;
      
      /**
       * @brief Construct a new Unbuffered Canvas object
       * 
       * @param display Reference to the display interface.
       */
      UnbufferedCanvas(DisplayT& display) : display_{display} {}
      
      /**
       * @brief Set the value of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param pixel The value of the pixel.
       */
      void setPixel(const size_t x, const size_t y, const ColorT& pixel)
      {
        if(y < Height && x < Width)
        {
            display_.setPixel(x, y, pixel.getValue());
        }
      }

      /**
       * @brief Clear the canvas with a given color.
       * 
       * @param color The color to clear the canvas with.
       */
      void clear(const ColorT& color)
      {
        display_.clear(color.getValue());
      }
    private:
      DisplayT& display_;
  };
}

#endif //EMBEDDED_GFX_UNBUFFERED_CANVAS_HPP