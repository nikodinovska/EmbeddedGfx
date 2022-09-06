#ifndef EMBEDDED_GFX_TEXT_HPP
#define EMBEDDED_GFX_TEXT_HPP

#include <cstdint>
#include <cstring>

#include "Drawable.hpp"
#include "Font.hpp"

namespace EmbeddedGfx
{
  template <uint8_t BufferSize, typename FontT, typename CanvasT>
  class Text : public Drawable<CanvasT>
  {
    public:

      Text(const char * const text, const Vector2D& pos = {})
        : position_{pos}
      {
        setString(text);
      }

      void draw(CanvasT& canvas) const override
      {
        auto textLength = std::strlen(text_);
        for(size_t iLetter = 0
            ; (iLetter < textLength) 
            && (iLetter < (canvas.getColumns() - static_cast<uint8_t>(position_.x))/FontT::width)
            ; ++iLetter)
        {
          const auto pixels = FontT::getCharacter(text_[iLetter]);
          for(size_t x = 0; x < FontT::width; ++x)
          {
            for(size_t y = 0; y < FontT::height; ++y)
            {
              canvas.setPixel(x + static_cast<uint8_t>(position_.x) + iLetter*FontT::width
                              , static_cast<uint8_t>(position_.y) + y
                              , pixels[x] & (1 << y));
            }
          }
        }
      }

      void setString(const char * const text)
      {
        std::strcpy(text_, text);
      }

      void setPosition(const Vector2D& pos)
      {
        position_ = pos;
      }

    private:
      char text_[BufferSize];
      Vector2D position_;
  };
}





#endif // EMBEDDED_GFX_TEXT_HPP