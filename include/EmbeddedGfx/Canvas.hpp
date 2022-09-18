#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>

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
    Normal = 0,
    Page   = 1,
    Color  = 2
  };

  /**
   * @brief Class representing canvas.
   * 
   * @tparam Height The number of rows.
   * @tparam Width The number of columns.
   * @tparam Type The canvas type.
   */
  template <size_t Height, size_t Width, CanvasType Type>
  class Canvas
  {
    public:
      using PixelT = uint8_t;
      static constexpr uint8_t PageSize = 8;
      using NormalMatrixT = std::array<std::array<PixelT, Width>, Height>;
      using PageMatrixT = std::array<std::array<PixelT, Width>, Height/PageSize + ((Height % PageSize) != 0)>;
      using ColorMatrixT = std::array<std::array<std::array<PixelT, 3>, Width>, Height>;
      using MatrixT = std::conditional_t<
                                  Type == CanvasType::Normal
                                , NormalMatrixT
                                , std::conditional_t<
                                        Type == CanvasType::Page
                                      , PageMatrixT
                                      , ColorMatrixT >>;

      Canvas() : matrix_{{}}
      {
      }

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
       * @brief Get the matrix representing the canvas.
       * 
       * @return const auto& The matrix of the canvas.
       */
      const auto& getMatrix() const
      {
        return matrix_;
      }

      /**
       * Clear the canvas.
       * 
       */
      void clear()
      {
        for(auto& row: matrix_)
        {
          for(auto& p: row)
          {
            p = 0;
          }
        }
      }

      /**
       * @brief Set the state of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param state true to set the pixel on, false to set it off.
       */
      void setPixel(const size_t x, const size_t y, const bool state = true)
      {
        if(y < Height && x < Width)
        {
          if constexpr (Type == CanvasType::Normal)
          {
            matrix_[y][x] = state;
          }
          else if constexpr(Type == CanvasType::Page)
          {
            if(state) matrix_[y/PageSize][x] |= 1 << (y % PageSize);
            else matrix_[y/PageSize][x] &= ~(1 << (y % PageSize));
          }
        }
      }

      using DrawableT = Drawable<Canvas>;
      /**
       * @brief Draw object on the canvas.
       * 
       * @param drawable Reference to drawable object.
       */
      void draw(const DrawableT& drawable)
      {
        drawable.draw(*this);
      }

      private:
        MatrixT matrix_;
  };
}