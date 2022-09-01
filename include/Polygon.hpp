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
  template <uint8_t Sides, typename CanvasT>
  class Polygon : public Shape<CanvasT>
  {
    public:
      Polygon(const std::array<Vector2D, Sides>& points)
        : points_ {points}
        {
        }
      
      void draw(CanvasT& canvas) const override
      {
        std::array<std::pair<float, uint8_t>, Sides> distances{};
        std::array<uint8_t, Sides> pointUsed{};
        for(uint8_t iPoint = 0; iPoint < Sides; ++iPoint)
        {
          // calculate the distances to every point
          for(uint8_t iOtherPoint = 0; iOtherPoint < Sides; ++iOtherPoint)
          {
            distances[iOtherPoint] = std::make_pair((points_[iPoint] - points_[iOtherPoint]).abs(), iOtherPoint);
          }
          // sort the distances
          std::sort(distances.begin(), distances.end(), [](auto a, auto b){
            return a.first < b.first;
          });
          // find the first unused point with minimum distance
          // skip the first element of distance, as it is related to the same point
          for(uint8_t iDistance = 1; iDistance < Sides; ++iDistance)
          {
            auto iOtherPoint = distances[iDistance].second;
            if(pointUsed[iOtherPoint] < 2)
            {
              Line<CanvasT> line(points_[iPoint], points_[iOtherPoint]);
              line.draw(canvas);
              ++pointUsed[iOtherPoint];
              break;
            }
          }
        }
        // there should be one point left with only one connection
        // and one point with zero connections
        // find them and connect them
        Vector2D point1, point2;
        bool firstFound = false;
        for(uint8_t iPoint = 0; iPoint < Sides; ++iPoint)
        {
          if(pointUsed[iPoint] != 2)
          {
            if(firstFound) point2 = points_[iPoint];
            else
            {
              point1 = points_[iPoint];
              firstFound = true;
            }
          }
        }
        Line<CanvasT> line(point1, point2);
        line.draw(canvas);
      }
      private:
        const std::array<Vector2D, Sides> points_;    
    };
}



#endif //EMBEDDED_GFX_POLYGON_HPP