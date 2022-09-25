#include <array>
#include <iostream>
#include <EmbeddedGfx/UnbufferedCanvas.hpp>
#include <EmbeddedGfx/Line.hpp>
#include <EmbeddedGfx/Ellipse.hpp>
#include <EmbeddedGfx/Circle.hpp>
#include <EmbeddedGfx/Polygon.hpp>
#include <EmbeddedGfx/Triangle.hpp>
#include <EmbeddedGfx/Rectangle.hpp>
#include <EmbeddedGfx/Text.hpp>
#include <EmbeddedGfx/Colors.hpp>

template<size_t Width, size_t Height>
class VirtualDisplay
{
  public:
    VirtualDisplay() : matrix_{{}} {}
    void setPixel(const size_t x, const size_t y, const bool pixel)
    {
      if(x < Width && y < Height)
      {
        matrix_[y][x] = pixel;
      }
    }

    void print() const
    {
      const auto rows = Height;
      const auto columns = Width;
      for(size_t x = 0; x < columns+2; ++x)
      {
        std::cout << "-";
      }
      std::cout << "\n";
      for(size_t y = 0; y < rows; ++y)
      {
        std::cout << "|";
        for(size_t x = 0; x < columns; ++x)
        {
          std::cout << ((matrix_[y][x]) ? 'X' : ' ');
        }
        std::cout << "| \n";
      }
      for(size_t x = 0; x < columns+2; ++x)
      {
        std::cout << "-";
      }
      std::cout << std::endl;
    }
  private:
    std::array<std::array<bool, Width>, Height> matrix_;
};

int main()
{
  using namespace EmbeddedGfx;
  static constexpr size_t height = 64;
  static constexpr size_t width = 128;
  VirtualDisplay<width, height> virtualDisplay;
  UnbufferedCanvas<width, height, CanvasType::Normal, ColorType::BlackAndWhite, decltype(virtualDisplay)> canvas(virtualDisplay);
  using CanvasT = decltype(canvas);

  // Line test
  Line<CanvasT> line{{1, 2}, {20, 10}, Colors::White};
  canvas.draw(line);

  // Ellipse test
  Ellipse<CanvasT> ellipse{{30, 30}, 10, 5};
  ellipse.setOutlineColor(Colors::White);
  canvas.draw(ellipse);

  // Circle test
  Circle<CanvasT> circle({60, 20}, 10);
  circle.setOutlineColor(Colors::White);
  canvas.draw(circle);

  // Polygon test
  Polygon<4, CanvasT> polygon({{{90.0f, 30.0f}, {100.0f, 50.0f}, {60.0f, 50.0f}, {110.0f, 30.0f}}});
  polygon.setOutlineColor(Colors::White);
  canvas.draw(polygon);

  // Triangle test
  Triangle<CanvasT> triangle({{{60.0f, 60.0f}, {50.0f, 50.0f}, {50.0f, 60.0f}}});
  triangle.setOutlineColor(Colors::White);
  canvas.draw(triangle);

  // Rectangle test
  Rectangle<CanvasT> rectangle{{10.0f, 50.0f}, 20.0f, 10.0f};
  rectangle.setOutlineColor(Colors::White);
  canvas.draw(rectangle);

  // Text test
  Text<100, Font<6, 8>, CanvasT> text("Text test !!!", {30.0f, 0.0f});
  text.setColor(Colors::White);
  canvas.draw(text);

  // print the canvas in the console
  virtualDisplay.print();
}