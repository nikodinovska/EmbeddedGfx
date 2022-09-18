#include <iostream>
#include <EmbeddedGfx/Canvas.hpp>
#include <EmbeddedGfx/Line.hpp>
#include <EmbeddedGfx/Ellipse.hpp>
#include <EmbeddedGfx/Circle.hpp>
#include <EmbeddedGfx/Polygon.hpp>
#include <EmbeddedGfx/Triangle.hpp>
#include <EmbeddedGfx/Rectangle.hpp>
#include <EmbeddedGfx/Text.hpp>

template <typename CanvasT>
void printCanvas(const CanvasT& canvas)
{
  auto rows = canvas.getHeight();
  auto columns = canvas.getWidth();
  const auto& matrix = canvas.getMatrix();
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
      std::cout << ((matrix[y][x] == 1) ? 'X' : ' ');
    }
    std::cout << "| \n";
  }
  for(size_t x = 0; x < columns+2; ++x)
  {
    std::cout << "-";
  }
  std::cout << std::endl;
}

int main()
{
  using namespace EmbeddedGfx;
  static constexpr size_t height = 64;
  static constexpr size_t width = 128;
  Canvas<width, height, CanvasType::Normal> canvas;
  using CanvasT = decltype(canvas);

  // Line test
  Line<CanvasT> line{{1, 2}, {20, 10}};
  canvas.draw(line);

  // Ellipse test
  Ellipse<CanvasT> ellipse{{30, 30}, 10, 5};
  canvas.draw(ellipse);

  // Circle test
  Circle<CanvasT> circle({60, 20}, 10);
  canvas.draw(circle);

  // Polygon test
  Polygon<4, CanvasT> polygon({{{90.0f, 30.0f}, {100.0f, 50.0f}, {60.0f, 50.0f}, {110.0f, 30.0f}}});
  canvas.draw(polygon);

  // Triangle test
  Triangle<CanvasT> triangle({{{60.0f, 60.0f}, {50.0f, 50.0f}, {50.0f, 60.0f}}});
  canvas.draw(triangle);

  // Rectangle test
  Rectangle<CanvasT> rectangle{{10.0f, 50.0f}, 20.0f, 10.0f};
  canvas.draw(rectangle);

  // Text test
  Text<100, Font<6, 8>, CanvasT> text("Text test !!!", {30.0f, 0.0f});
  canvas.draw(text);

  // print the canvas in the console
  printCanvas(canvas);
}