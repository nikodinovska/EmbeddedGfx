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
   * @tparam ColorT The color representation type.
   * @tparam DisplayT The type for the display device.
   * @note DisplayT must have method setPixel(x, y, value).
   */
  template<size_t Width, size_t Height, CanvasType Type, ColorType ColorRep, typename DisplayT>
  class UnbufferedCanvas
    : public Canvas<Width, Height, Type, ColorRep
                  , UnufferedCanvas<Width, Height, Type, ColorRep>>
  {
    using BaseT = Canvas<Width, Height, Type, ColorRep, UnbufferedCanvas>;
    public:
      using PixelT = typename BaseT::PixelT;
      using ColorAndSimpleMatrixT = std::array<std::array<PixelT, Width>, Height>;
      static constexpr uint8_t PageSize = 8;
      using PageMatrixT = std::array<std::array<PixelT, Width>, Height/PageSize + ((Height % PageSize) != 0)>; 
      using MatrixT = std::conditional_t<
                          Type == CanvasType::Page
                        , PageMatrixT
                        , ColorAndSimpleMatrixT>;
      /**
       * @brief Construct a new Unbuffered Canvas object
       * 
       * @param display Reference to the display interface.
       */
      UnbufferedCanvas(DisplayT& display) : display_{display} {}
      /**
       * @brief Get the matrix representing the canvas.
       * 
       * @return const auto& The matrix of the canvas.
       */
      const auto& getMatrix() const { return matrix_; }
      
      /**
       * @brief Set the value of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param pixel The value of the pixel.
       */
      void setPixel(const size_t x, const size_t y, const PixelT& pixel)
      {
        if(y < Height && x < Width)
        {
            display_.setPixel(x, y, pixel.getValue());
        }
      }
    private:
      DisplayT& display_;
  };
}

#endif //EMBEDDED_GFX_UNBUFFERED_CANVAS_HPP