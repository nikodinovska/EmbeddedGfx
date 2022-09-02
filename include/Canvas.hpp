#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>

#include "Drawable.hpp"

enum class CanvasType
{
  Normal = 0,
  Page   = 1,
  Color  = 2
};

namespace EmbeddedGfx
{
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

      void setPixel(const size_t x, const size_t y)
      {
        if(y < Rows && x < Columns)
        {
          if constexpr (Type == CanvasType::Normal)
          {
            matrix_[y][x] = 1;
          }
          else if constexpr(Type == CanvasType::Page)
          {
            matrix_[y/PageSize][x] |= 1 << (y % PageSize);
          }
        }
      }

      void clearPixel(const size_t x, const size_t y)
      {
        if(y < Rows && x < Columns)
        {
          if constexpr (Type == CanvasType::Normal)
          {
            matrix_[y][x] = 0;
          }
          else if constexpr(Type == CanvasType::Page)
          {
            matrix_[y/PageSize][x] &= ~(1 << (y % PageSize));
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