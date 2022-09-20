#ifndef EMBEDDED_GFX_POLYGON_HPP
#define EMBEDDED_GFX_POLYGON_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstddef>
#include <utility>

#include "Shape.hpp"
#include "Vector2D.hpp"
#include "Line.hpp"

namespace EmbeddedGfx
{
  /**
   * @brief Class representing convex polygon shape.
   * 
   * @tparam Sides The number of sides for the polygon.
   * @tparam CanvasT The type of the canvas.
   */
  template <uint8_t Sides, typename CanvasT>
  class Polygon : public Shape<CanvasT>
  {
    public:
      using PixelT = typename CanvasT::PixelT;
    public:
      /**
       * @brief Construct a new Polygon object
       * 
       * @param points The coordinates of the points
       * for the polygon.
       */
      Polygon(const std::array<Vector2Df, Sides>& points)
        : points_{points}
      {
        // calculate the center of mass point
        Vector2Df massCenter{};
        for(const auto& point: points_) massCenter += point;
        massCenter /= Sides;
        // shift the center to the center of mass and 
        // sort the points based on polar coordinates
        struct PolarCoordinates
        {
          float abs;
          float angle;
        };
        std::array<std::pair<Vector2Df, PolarCoordinates>, Sides> pointsPolarCoordinates{};
        std::transform(points_.cbegin(), points_.cend(), pointsPolarCoordinates.begin()
                      , [&massCenter](const Vector2Df& point) { 
                          return std::make_pair(
                                point
                              , PolarCoordinates{
                                  (point - massCenter).abs()
                                , (point - massCenter).angle()
                                }
                          );
                        });
        std::sort(pointsPolarCoordinates.begin(), pointsPolarCoordinates.end()
                , [](const auto& v1, const auto& v2) {
                    return (v1.second.angle < v2.second.angle)
                        || (v1.second.abs < v2.second.abs);
                  });
        for(size_t iPoint = 0; iPoint < Sides; ++iPoint)
        {
          points_[iPoint] = pointsPolarCoordinates[iPoint].first;
        }
      }
      
      /**
       * @brief Draw the polygon on the canvas.
       * 
       * @param canvas Reference to the canvas.
       */
      void draw(CanvasT& canvas) const override
      {
        for(size_t iPoint = 0; iPoint < Sides - 1; ++iPoint)
        {
          Line<CanvasT> line{points_[iPoint], points_[iPoint + 1], this->outlineColor_};
          line.draw(canvas);
        }
        Line<CanvasT> line{points_[0], points_[Sides - 1], this->outlineColor_};
        line.draw(canvas);
      }
      private:
        std::array<Vector2Df, Sides> points_;
    };
}



#endif //EMBEDDED_GFX_POLYGON_HPP