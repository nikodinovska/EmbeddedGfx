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
      using PageMatrixT = std::array<std::array<uint8_t, Width>, Height/PageSize + ((Height % PageSize) != 0)>; 
      using MatrixT = std::conditional_t<
                          Type == CanvasType::Page
                        , PageMatrixT
                        , ColorAndSimpleMatrixT>;
      BufferedCanvas() : matrix_{{}}
      {
        if constexpr(Type == CanvasType::Page)
        {
          static_assert(ColorRep == ColorType::BlackAndWhite, "Color type must be black and white when using Page mode.");
        }
      }

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
          if constexpr (Type == CanvasType::Normal)
          {
            matrix_[y][x] = matrix_[y][x] = pixel.getValue();
          }
          else if constexpr(Type == CanvasType::Page)
          {
            if(pixel.getValue()) matrix_[y/PageSize][x] |= 1 << (y % PageSize);
            else matrix_[y/PageSize][x] &= ~(1 << (y % PageSize));
          }
        }
      }

      /**
       * @brief Clear the canvas with a given color.
       * 
       * @param color The color to clear the canvas with.
       */
      void clear(const ColorT& color)
      {
        auto value = color.getValue();
        for(size_t y = 0; y < matrix_.size(); ++y)
        {
          for(size_t x = 0; x < matrix_[0].size(); ++x)
          {
            matrix_[y][x] = value;
          }
        }
      }
    private:
      MatrixT matrix_;
  };
}

#endif //EMBEDDED_GFX_BUFFERED_CANVAS_HPP