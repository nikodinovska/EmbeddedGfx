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
  
  /**
   * RGB565 colors representation.
   * Uses 5, 6 and 5 bits for red, green and blue colors.
   * 
   */
  union RGB565
  {
    struct
    {
      uint16_t red : 5;
      uint16_t green : 6;
      uint16_t blue : 5;
    } colors;

    uint16_t value;
  };

  /**
   * RGB666 colors representation.
   * Uses 6 bits for each red, green and blue colors.
   * 
   */
  union RGB666
  {
    struct
    {
      uint32_t red : 6;
      uint32_t green : 6;
      uint32_t blue : 6;
    } colors;

    uint32_t value;
  };

  /**
   * RGB888 color representation.
   * Uses 1 byte for each red, green and blue colors.
   * 
   */
  struct RGB888
  {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  };
}

#endif //EMBEDDED_GFX_COLOR_HPP