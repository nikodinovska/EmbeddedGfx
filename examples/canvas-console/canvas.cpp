#include <iostream>
#include <Canvas.hpp>
#include <Line.hpp>
#include <Ellipse.hpp>

int main()
{
  using namespace EmbeddedGfx;
  static constexpr size_t rows = 64;
  static constexpr size_t columns = 64;
  Canvas<rows, columns> canvas;

  Line<decltype(canvas)> line(1, 2, 20, 0);
  canvas.draw(line);

  Ellipse<decltype(canvas)> ellipse(30, 30, 20, 5);
  canvas.draw(ellipse);

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
      std::cout << ((canvas.getMatrix()[y][x] == 1) ? 'X' : ' ');
    }
    std::cout << "| \n";
  }
  for(size_t x = 0; x < columns+2; ++x)
  {
    std::cout << "-";
  }
}