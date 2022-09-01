#ifndef EMBEDDED_GFX_VECTOR_2D_HPP
#define EMBEDDED_GFX_VECTOR_2D_HPP

#include <cstddef>
#include <cmath>

namespace EmbeddedGfx
{
  struct Vector2D
  {
    float x, y;

    Vector2D(float x=0.0f, float y=0.0f) : x(x), y(y)
    {
    }

    Vector2D& operator+=(const Vector2D& vector)
    {
      this->x = this->x + vector.x;
      this->y = this->y + vector.y;
      return *this;
    }

    Vector2D operator+(const Vector2D& vector) const
    {
      Vector2D temp(*this);
      temp += vector;
      return temp;
    }

    Vector2D& operator-=(const Vector2D& vector)
    {
      this->x = this->x - vector.x;
      this->y = this->y - vector.y;
      return *this;
    }

    Vector2D operator-(const Vector2D& vector) const
    {
      Vector2D temp(*this);
      temp -= vector;
      return temp;
    }

    template <typename ScalarT>
    Vector2D& operator*=(const ScalarT scalar)
    {
      x *= scalar;
      y *= scalar;
      return *this;
    }

    template <typename ScalarT>
    Vector2D operator*(const ScalarT scalar) const
    {
      Vector2D temp(*this);
      temp *= scalar;
      return temp;
    }

    template <typename Scalar>
    friend Vector2D operator*(const Scalar scalar, const Vector2D& vector)
    {
      return vector * scalar;
    }

    template <typename ScalarT>
    Vector2D& operator/=(const ScalarT scalar)
    {
      x /= scalar;
      y /= scalar;
      return *this;
    }

    template <typename ScalarT>
    Vector2D operator/(const ScalarT scalar) const
    {
      Vector2D temp(*this);
      temp /= scalar;
      return temp;
    }

    template <typename ScalarT>
    friend Vector2D operator/(const ScalarT scalar, const Vector2D& vector)
    {
      return vector / scalar;
    }

    bool operator!=(const Vector2D& vector) const
    {
      static constexpr float EPS = 10e-8f;
      return (std::fabs(this->x - vector.x) >= EPS || std::fabs(this->y - vector.y) >= EPS);
    }

    bool operator==(const Vector2D& vector) const
    {
      return !(*this != vector);
    }

    size_t abs() const
    {
      return std::sqrt(x * x + y * y);
    }

    size_t angle() const
    {
      return std::atan2(y, x);
    }

    Vector2D rounded() const
    {
      Vector2D vector(*this);
      vector.x = std::roundf(vector.x);
      vector.y = std::roundf(vector.y);
      return vector;
    }
  };
}


#endif //EMBEDDED_GFX_VECTOR_2D_HPP