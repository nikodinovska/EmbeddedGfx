#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>

#include "Drawable.hpp"
#include "Vector2D.hpp"

namespace EmbeddedGfx
{
  enum class CanvasType
  {
    Normal = 0,
    Page   = 1,
    Color  = 2
  };
  
  template <size_t Rows, size_t Columns, CanvasType Type>
  class Canvas
  {
    public:
      using PixelT = uint8_t;
      static constexpr uint8_t PageSize = 8;
      using NormalMatrixT = std::array<std::array<PixelT, Columns>, Rows>;
      using PageMatrixT = std::array<std::array<PixelT, Columns>, Rows/PageSize + ((Rows % PageSize) != 0)>;
      using ColorMatrixT = std::array<std::array<std::array<PixelT, 3>, Columns>, Rows>;
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

      size_t getRows() const
      {
        return Rows;
      }

      size_t getColumns() const
      {
        return Columns;
      }

      size_t getSize() const
      {
        if constexpr (Type == CanvasType::Normal)
        {
          return Rows * Columns;
        }
        else if constexpr (Type == CanvasType::Page)
        {
          return Rows * Columns / PageSize;
        }
      }

      const auto& getMatrix() const
      {
        return matrix_;
      }

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

      void setPixel(const size_t x, const size_t y, const bool state = true)
      {
        if(y < Rows && x < Columns)
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
      void draw(const DrawableT& drawable)
      {
        drawable.draw(*this);
      }

      private:
        MatrixT matrix_;
  };
}