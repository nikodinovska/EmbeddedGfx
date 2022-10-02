#ifndef EMBEDDED_GFX_COLOR_HPP
#define EMBEDDED_GFX_COLOR_HPP

#include <cstdint>

namespace EmbeddedGfx
{ 
  struct Color
  {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    constexpr Color() : Color{0, 0, 0} { }

    constexpr Color(const uint8_t r, const uint8_t g, const uint8_t b)
      : red(r), green(g), blue(b) { }
  };

  namespace Colors
  {
    static constexpr Color Black{0, 0, 0};
    static constexpr Color White{255, 255, 255};
    static constexpr Color Red{255, 0, 0};
    static constexpr Color Green{0, 255, 0};
    static constexpr Color Blue{0, 0, 255};
    static constexpr Color Yellow{255, 255, 0};
    static constexpr Color Cyan{0, 255, 255};
    static constexpr Color Magenta{255, 0, 255};
  }

  /**
   * RGB888 color representation.
   * Uses 1 byte for each red, green and blue colors.
   * 
   */

  struct RGB888: public Color
  {
    using Type = uint32_t;
    constexpr RGB888() { }
    constexpr RGB888(const Color& color) : Color{color} { }
    constexpr Type getValue() const
    {
      return (red | (green << 8) | (blue << 16));
    }
  };
  
  /**
   * RGB565 colors representation.
   * Uses 5, 6 and 5 bits for red, green and blue colors.
   * 
   */
  struct RGB565: public Color
  {
    using Type = uint16_t;
    constexpr RGB565() { }
    constexpr RGB565(const Color& color) : Color{color} { }
    constexpr Type getValue() const
    {
      return (((red & 0xF8) >> 3) | (((green & 0xFC) >> 2) << 5) | (((blue & 0xF8) >> 2) << 11)); 
    }
  };


  struct RGB666: public Color
  {
    using Type = uint32_t;
    constexpr RGB666() { }
    constexpr RGB666(const Color& color) : Color{color} { }
    constexpr Type getValue() const
    {
      return ((((red & 0xFC) >> 2)) | ((green & 0xFC) << 6) | ((blue & 0xFC) << 12));
    }
  };

  struct BlackAndWhite: public Color
  {
    using Type = bool;
    constexpr BlackAndWhite() { }
    constexpr BlackAndWhite(const Color& color) : Color{color} { }
    constexpr Type getValue() const
    {
      return ((red & green & blue) == 255);
    }
  };
}

#endif //EMBEDDED_GFX_COLOR_HPP