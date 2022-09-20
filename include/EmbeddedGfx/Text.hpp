#ifndef EMBEDDED_GFX_TEXT_HPP
#define EMBEDDED_GFX_TEXT_HPP

#include <cstdint>
#include <cstring>

#include "Drawable.hpp"
#include "Font.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing text.
   * 
   * @tparam BufferSize The number of characters the buffer can hold.
   * @tparam FontT The type of the font.
   * @tparam CanvasT The type of the canvas.
   */
  template <uint8_t BufferSize, typename FontT, typename CanvasT>
  class Text : public Drawable<CanvasT>
  {
    public:
      using PixelT = typename CanvasT::PixelT;
    public:
      /**
       * @brief Construct a new Text object.
       * 
       * @param text The text to be stored.
       * @param pos The coordinates of the top-left corner.
       */
      Text(const char * const text, const Vector2Df& pos = {})
        : position_{pos}
      {
        setString(text);
      }

      void setColor(const PixelT& color)
      {
        color_ = color;
      }

      /**
       * @brief Draw the text on the canvas.
       * 
       * @param canvas Reference to the canvas.
       */
      void draw(CanvasT& canvas) const override
      {
        auto textLength = std::strlen(text_);
        for(size_t iLetter = 0
            ; (iLetter < textLength) 
            && (iLetter < (canvas.getWidth() - static_cast<uint8_t>(position_.x))/FontT::width)
            ; ++iLetter)
        {
          const auto pixels = FontT::getCharacter(text_[iLetter]);
          for(size_t x = 0; x < FontT::width; ++x)
          {
            for(size_t y = 0; y < FontT::height; ++y)
            {
              canvas.setPixel(x + static_cast<uint8_t>(position_.x) + iLetter * FontT::width
                              , static_cast<uint8_t>(position_.y) + y
                              , (pixels[x] & (1 << y)) ? color_ : Colors::Black);
            }
          }
        }
      }

      /**
       * @brief Set the text content.
       * 
       * @param text C-string text.
       */
      void setString(const char * const text)
      {
        if(std::strlen(text) >= BufferSize) return;
        std::strcpy(text_, text);
      }

      /**
       * @brief Set the top-left corner of the text.
       * 
       * @param pos Coordinates of the top-left corner.
       */
      void setPosition(const Vector2Df& pos)
      {
        position_ = pos;
      }

    private:
      char text_[BufferSize];
      Vector2Df position_;
      PixelT color_;
  };
}





#endif // EMBEDDED_GFX_TEXT_HPP