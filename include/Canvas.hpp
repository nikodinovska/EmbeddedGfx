#include <array>
#include <cstddef>
#include <cstdint>

#include "Shape.hpp"

namespace EmbeddedGfx
{
  template <size_t Rows, size_t Columns>
  class Canvas
  {
    public:
      using PixelT = uint8_t;
      using MatrixT = std::array<std::array<PixelT, Columns>, Rows>;

      Canvas()
      : matrix_ ({})
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

      void setPixel(const size_t x, const size_t y)
      {
        if(y < Rows && x < Columns)
        {
          matrix_[y][x] = 1;
        }
      }

      using ShapeT = Shape<Canvas>;
      void draw(const ShapeT& shape)
      {
        shape.draw(*this);
      }

      private:
        MatrixT matrix_;
  };
}