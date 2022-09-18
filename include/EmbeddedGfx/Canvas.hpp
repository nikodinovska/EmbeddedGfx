#include <array>
#include <cstddef>
#include <cstdint>
#include <cmath>

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
    Simple,
    Page,
    Color
  };

  /**
   * @brief Template class for canvas.
   * 
   * @tparam Width The width of the canvas in pixels.
   * @tparam Height The height of the canvas in pixels.
   * @tparam Type The type of the canvas.
   * @tparam Unbuffered true if no buffer is needed.
   * @tparam ColorT The color representation type.
   * @tparam DisplayT The type of the display on which the canvas will be drawn.
   * Should be used in Unbuffered mode only.
   */
  template<size_t Width, size_t Height
        , CanvasType Type, bool Unbuffered = false
        , ColorType ColorRep = ColorType::BlackAndWhite
        , typename DisplayT = void>
  class Canvas {};

  /**
   * @brief Class representing canvas for Simple and Page unbuffered canvas types.
   * 
   * @tparam Width The number of columns.
   * @tparam Height The number of rows.
   * @tparam Type The canvas type.
   */
  template <size_t Width, size_t Height, CanvasType Type>
  class Canvas<Width, Height, Type, false, ColorType::BlackAndWhite, void>
  {
    public:
      using PixelT = uint8_t;
      static constexpr uint8_t PageSize = 8;
      using NormalMatrixT = std::array<std::array<PixelT, Width>, Height>;
      using PageMatrixT = std::array<std::array<PixelT, Width>, Height/PageSize + ((Height % PageSize) != 0)>;
      using MatrixT = std::conditional_t<
                                  Type == CanvasType::Simple
                                , NormalMatrixT
                                , PageMatrixT>;

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
          if constexpr (Type == CanvasType::Simple)
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

  /**
   * @brief Class representing canvas for Color buffered canvas types.
   * 
   * @tparam Width The number of columns.
   * @tparam Height The number of rows.
   * @tparam ColorRep The colors representation.
   */
  template<size_t Width, size_t Height, ColorType ColorRep>
  class Canvas<Width, Height, CanvasType::Color, false, ColorRep, void>
  {
    public:
      using PixelT = std::conditional_t<
                        ColorRep == ColorType::RGB565
                      , RGB565
                      , std::conditional_t<
                            ColorRep == ColorType::RGB666
                          , RGB666
                          , RGB888
                        >
                      >;
      using ColorMatrixT = std::array<std::array<PixelT, Width>, Height>;

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
            p = {};
          }
        }
      }

      /**
       * @brief Set the color of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param color The color of the pixel.
       */
      void setPixel(const size_t x, const size_t y, const PixelT& color)
      {
        if(y < Height && x < Width)
        {
          matrix_[y][x] = color;
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
      ColorMatrixT matrix_;
  };

  /**
   * @brief Class representing canvas for Color unbuffered canvas types.
   * 
   * @tparam Width The number of columns.
   * @tparam Height The number of rows.
   * @tparam ColorRep The colors representation.
   * @tparam DisplayT The type for the physical display.
   * This type must have setPixel(x, y, value) method.
   */
  template<size_t Width, size_t Height, ColorType ColorRep, typename DisplayT>
  class Canvas<Width, Height, CanvasType::Color, true, ColorRep, DisplayT>
  {
    public:
      using PixelT = std::conditional_t<
                        ColorRep == ColorType::RGB565
                      , RGB565
                      , std::conditional_t<
                            ColorRep == ColorType::RGB666
                          , RGB666
                          , RGB888
                        >
                      >;

      Canvas(DisplayT& display) : display_{display}
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
       * Clear the canvas.
       * 
       */
      void clear()
      {
        ///@todo
      }

      /**
       * @brief Set the color of individual pixel.
       * 
       * @param x The x-coordinate of the pixel.
       * @param y The y-coordinate of the pixel.
       * @param color The color of the pixel.
       */
      void setPixel(const size_t x, const size_t y, const PixelT& color)
      {
        if(y < Height && x < Width)
        {
          display_.setPixel(x, y, color.value);
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
      DisplayT& display_;
  };
}