#ifndef EMBEDDED_GFX_BUFFERED_CANVAS_HPP
#define EMBEDDED_GFX_BUFFERED_CANVAS_HPP

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
   */
  template<size_t Width, size_t Height, CanvasType Type, ColorType ColorRep>
  class BufferedCanvas
    : public Canvas<Width, Height, Type, ColorRep
                  , BufferedCanvas<Width, Height, Type, ColorRep>>
  {
    using BaseT = Canvas<Width, Height, Type, ColorRep, BufferedCanvas>;
    public:
      using ColorT = typename BaseT::ColorT;
      using PixelT = typename BaseT::PixelT;
      using ColorAndSimpleMatrixT = std::array<std::array<PixelT, Width>, Height>;
      static constexpr uint8_t PageSize = 8;
      using PageMatrixT = std::array<std::array<PixelT, Width>, Height/PageSize + ((Height % PageSize) != 0)>; 
      using MatrixT = std::conditional_t<
                          Type == CanvasType::Page
                        , PageMatrixT
                        , ColorAndSimpleMatrixT>;
      BufferedCanvas() : matrix_{{}} {}
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
      void setPixel(const size_t x, const size_t y, const ColorT& pixel)
      {
        if(y < Height && x < Width)
        {
          matrix_[y][x] = pixel.getValue();
        }
      }
    private:
      MatrixT matrix_;
  };
}

#endif //EMBEDDED_GFX_BUFFERED_CANVAS_HPP