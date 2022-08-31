#ifndef EMBEDDED_GFX_DRAWABLE
#define EMBEDDED_GFX_DRAWABLE

namespace EmbeddedGfx
{
  template<typename CanvasT>
  class Drawable
  {
    public:
      virtual void draw(CanvasT& canvas) const = 0;
  };
}

#endif //EMBEDDED_GFX_DRAWABLE