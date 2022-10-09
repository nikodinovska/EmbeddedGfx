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
        using PolarCoordinates = std::pair<float, float>;  //< first is angle, second is abs
        using HelperPair = std::pair<Vector2Df, PolarCoordinates>;
        std::array<HelperPair, Sides> pointsPolarCoordinates{};
        std::transform(points_.cbegin(), points_.cend(), pointsPolarCoordinates.begin()
                      , [&massCenter](const Vector2Df& point) -> HelperPair { 
                          return {
                                point
                              , {
                                  (point - massCenter).angle()
                                , (point - massCenter).abs()
                                }
                          };
                        });
        std::sort(pointsPolarCoordinates.begin(), pointsPolarCoordinates.end()
                , [](const auto& v1, const auto& v2) {
                    static constexpr float eps = 1e-7f;
                    return (v1.second.first < v2.second.first)
                        || ((std::abs(v1.second.first - v2.second.first) < eps)
                          && (v1.second.second < v2.second.second));
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
        if(this->fillColor_)
        {
          // scanline fill algorithm
          ///@todo special cases
          // 1. find ymin and ymax
          const auto [yminFloat, ymaxFloat] = std::minmax_element(points_.cbegin(), points_.cend()
                                              , [](const Vector2Df& a, const Vector2Df& b) {
                                                      return a.y < b.y;
                                                  });
          const size_t ymin = static_cast<size_t>(std::roundf(yminFloat->y));
          const size_t ymax = static_cast<size_t>(std::roundf(ymaxFloat->y));
          // 2. find line equations for sides of the polygon
          std::array<std::pair<std::optional<float>, float>, Sides> sidesEqs{};  //< first element is k, second is n
          for(size_t i = 0; i < points_.size(); ++i)
          {
            const size_t j = (i == (points_.size() - 1)) ? 0 : i + 1;
            static constexpr float eps = 1e-7f;
            // check if line is vertical
            if(std::abs(points_[j].x - points_[i].x) < eps)
            {
              sidesEqs[i].first = std::nullopt;
              sidesEqs[i].second = points_[i].x;
            }
            else
            {
              sidesEqs[i].first = (points_[j].y - points_[i].y) / (points_[j].x - points_[i].x);
              sidesEqs[i].second = points_[i].y - *(sidesEqs[i]).first * points_[i].x;
            }
          }
          // 3. draw scanlines and find intersections with polygon sides
          for(size_t y = ymin; y <= ymax; ++y)
          {
            static constexpr size_t maxIntersections = 10;
            std::array<size_t, maxIntersections> xmArray{};
            size_t iIntersection = 0;  //< index for xmArray
            for(size_t i = 0; i < sidesEqs.size(); ++i)
            {
              // calculate xm
              float xm{};
              // check if line is vertical
              if(sidesEqs[i].first)
              {
                xm = (y - sidesEqs[i].second) / *(sidesEqs[i]).first;
              }
              else
              {
                xm = sidesEqs[i].second;
              }
              // check if xm is in bounds
              // find x bounds
              const auto [x1, x2] = std::minmax(points_[i].x, ((i == sidesEqs.size() - 1) ? points_[0].x : points_[i + 1].x));
              if(xm >= x1 && xm <= x2)
              {
                xmArray[iIntersection++] = static_cast<size_t>(std::roundf(xm));
              }
            }
            // 4. sort xm array
            std::sort(xmArray.begin(), xmArray.begin() + iIntersection);
            // 5. fill the cells between two consecutive xms
            if(iIntersection > 1)
            {
              for(size_t i = 0; i < iIntersection - 1; i += 2)
              {
                for(size_t x = xmArray[i]; x <= xmArray[i + 1]; ++x)
                {
                  canvas.setPixel(x, y, *(this->fillColor_));
                }
              }
            }
          }
        }
        if(this->outlineColor_)
        {
          for(size_t iPoint = 0; iPoint < Sides - 1; ++iPoint)
          {
            Line<CanvasT> line{points_[iPoint], points_[iPoint + 1], *(this->outlineColor_)};
            line.draw(canvas);
          }
          Line<CanvasT> line{points_[0], points_[Sides - 1], *(this->outlineColor_)};
          line.draw(canvas);
        }
      }
      private:
        std::array<Vector2Df, Sides> points_;
    };
}



#endif //EMBEDDED_GFX_POLYGON_HPP