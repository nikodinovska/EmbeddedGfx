#ifndef EMBEDDED_GFX_DRAWABLE
#define EMBEDDED_GFX_DRAWABLE

namespace EmbeddedGfx
{
  /**
   * @brief Interace for drawable objects on
   * the canvas.
   * 
   * @tparam CanvasT Type of the canvas.
   */
  template<typename CanvasT>
  class Drawable
  {
    public:
      /**
       * @brief Draw the object on the canvas.
       * 
       * @param canvas Reference to the canvas.
       */
      virtual void draw(CanvasT& canvas) const = 0;
  };
}

#endif //EMBEDDED_GFX_DRAWABLE