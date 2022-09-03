#include <iostream>
#include <Canvas.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>
#include <Circle.hpp>
#include <Polygon.hpp>
#include <Triangle.hpp>
#include <Square.hpp>
#include <Text.hpp>

template <typename CanvasT>
void printCanvas(const CanvasT& canvas)
{
  auto rows = canvas.getRows();
  auto columns = canvas.getColumns();
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
  static constexpr size_t rows = 64;
  static constexpr size_t columns = 64;
  Canvas<rows, columns, CanvasType::Normal> canvas;

  Line<decltype(canvas)> line(1, 2, 20, 0);
  canvas.draw(line);

  Ellipse<decltype(canvas)> ellipse(30, 30, 20, 5);
  canvas.draw(ellipse);

  Circle<decltype(canvas)> circle(30, 10, 10);
  canvas.draw(circle);

  Polygon<4, decltype(canvas)> polygon({{{40.0f, 40.0f}, {40.0f, 50.0f}, {50.0f, 50.0f}, {60.0f, 30.0f}}});
  canvas.draw(polygon);

  Triangle<decltype(canvas)> triangle({{{60.0f, 60.0f}, {50.0f, 50.0f}, {50.0f, 60.0f}}});
  canvas.draw(triangle);

  printCanvas(canvas);
  canvas.clear();

  Square<decltype(canvas)> square({10.0f, 10.0f, 10.0f});
  canvas.draw(square);

  printCanvas(canvas);

  canvas.clear();
  Text<100, Font<6, 8>, decltype(canvas)> text("Ange");
  canvas.draw(text);

  printCanvas(canvas);
  
}