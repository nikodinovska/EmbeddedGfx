#ifndef EMBEDDED_GFX_COLOR_HPP
#define EMBEDDED_GFX_COLOR_HPP

#include <cstdint>

namespace EmbeddedGfx
{
  /**
   * Possible color representations.
   * 
   */
  enum class ColorType
  {
    BlackAndWhite,
    RGB565,
    RGB666,
    RGB888
  };
  
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
    constexpr RGB888() { }
    constexpr RGB888(const Color& color) : Color{color} { }
    constexpr uint32_t getValue() const
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
    constexpr RGB565() { }
    constexpr RGB565(const Color& color) : Color{color} { }
    constexpr uint16_t getValue() const
    {
      return (red | (green << 5) | (blue << 11)); 
    }
  };


  struct RGB666: public Color
  {
    constexpr RGB666() { }
    constexpr RGB666(const Color& color) : Color{color} { }
    constexpr uint32_t getValue() const
    {
      return (red | (green << 6) | (blue << 12));
    }
  };

  struct BlackandWhite: public Color
  {
    constexpr BlackandWhite() { }
    constexpr BlackandWhite(const Color& color) : Color{color} { }
    constexpr bool getValue() const
    {
      return ((red & green & blue) == 255);
    }
  };
}

#endif //EMBEDDED_GFX_COLOR_HPP