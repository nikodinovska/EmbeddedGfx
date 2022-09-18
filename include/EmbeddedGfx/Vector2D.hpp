#ifndef EMBEDDED_GFX_VECTOR_2D_HPP
#define EMBEDDED_GFX_VECTOR_2D_HPP

#include <cstddef>
#include <cmath>
#include <type_traits>

namespace EmbeddedGfx
{
  /**
   * @brief Two dimensional vector class.
   * 
   * @tparam CoordinatesT Type for the coordinates of the vector.
   * @note CoordinatesT must be arithmetic type.
   */
  template <
      typename CoordinatesT
    , typename = typename std::enable_if_t<std::is_arithmetic_v<CoordinatesT>, CoordinatesT>
  >
  struct Vector2D
  {
    CoordinatesT x, y;

    /**
     * @brief Construct a new Vector2D object
     * 
     * @param x The value for the x-coordinate.
     * @param y The value for the y-coordinate.
     */
    Vector2D(CoordinatesT x = {}, CoordinatesT y={})
      : x{x}, y{y}
    {
    }

    /**
     * @brief Add two vectors and return
     * reference to the lhs vector.
     * 
     * @param vector The rhs vector.
     * @return Vector2D& Reference to the lhs vector.
     */
    Vector2D& operator+=(const Vector2D& vector)
    {
      this->x = this->x + vector.x;
      this->y = this->y + vector.y;
      return *this;
    }

    /**
     * @brief Add two vectors and return new vector.
     * 
     * @param vector The rhs vector.
     * @return Vector2D The resulting vector.
     */
    Vector2D operator+(const Vector2D& vector) const
    {
      Vector2D temp(*this);
      temp += vector;
      return temp;
    }

    /**
     * @brief Subtract two vectors and return reference
     * to the lhs vector.
     * 
     * @param vector The rhs vector.
     * @return Vector2D& Reference to the lhs vector.
     */
    Vector2D& operator-=(const Vector2D& vector)
    {
      this->x = this->x - vector.x;
      this->y = this->y - vector.y;
      return *this;
    }

    /**
     * @brief Subtract two vectors and return new vector.
     * 
     * @param vector The rhs vector.
     * @return Vector2D The resulting vector.
     */
    Vector2D operator-(const Vector2D& vector) const
    {
      Vector2D temp(*this);
      temp -= vector;
      return temp;
    }

    /**
     * @brief Negate the vector coordinates and return
     * new vector.
     * 
     * @return Vector2D The resulting vector.
     */
    Vector2D operator-()
    {
      Vector2D vector;
      vector.x = -this->x;
      vector.y = -this->y;
    }

    /**
     * @brief Multiply vector by a scalar and return
     * reference to the lhs vector.
     * 
     * @tparam ScalarT The type of the scalar. Must be
     * arithmetic type.
     * @param scalar The scalar value.
     * @return Vector2D& Reference to the lhs vector.
     */
    template <
        typename ScalarT
      , typename = typename std::enable_if_t<std::is_arithmetic_v<ScalarT>, ScalarT>
    >
    Vector2D& operator*=(const ScalarT scalar)
    {
      x *= scalar;
      y *= scalar;
      return *this;
    }

    /**
     * @brief Multiply vector by a scalar and return
     * new vector.
     * 
     * @tparam ScalarT The type of the scalar. Must be
     * arithmetic type.
     * @param scalar The scalar value.
     * @return Vector2D The resulting vector.
     */
    template <
        typename ScalarT
      , typename = typename std::enable_if_t<std::is_arithmetic_v<ScalarT>, ScalarT>
    >
    Vector2D operator*(const ScalarT scalar) const
    {
      Vector2D temp(*this);
      temp *= scalar;
      return temp;
    }

    /**
     * @brief Multiply vector by a scalar and return
     * new vector.
     * 
     * @tparam ScalarT The type of the scalar. Must be
     * arithmetic type.
     * @param scalar The scalar value.
     * @param vector The vector operand.
     * @return Vector2D The resulting vector.
     */
    template <
        typename ScalarT
      , typename = typename std::enable_if_t<std::is_arithmetic_v<ScalarT>, ScalarT>
    >
    friend Vector2D operator*(const ScalarT scalar, const Vector2D& vector)
    {
      return vector * scalar;
    }

    /**
     * @brief Divide vector by a scalar and return reference
     * to the lhs vector.
     * 
     * @tparam ScalarT The type of the scalar. Must be
     * arithmetic type.
     * @param scalar The scalar value.
     * @return Vector2D& Reference to the lhs vector.
     */
    template <
        typename ScalarT
      , typename = typename std::enable_if_t<std::is_arithmetic_v<ScalarT>, ScalarT>
    >
    Vector2D& operator/=(const ScalarT scalar)
    {
      x /= scalar;
      y /= scalar;
      return *this;
    }

    /**
     * @brief Divide vector by a scalar and return
     * new vector.
     * 
     * @tparam ScalarT The type of the scalar. Must be
     * arithmetic type.
     * @param scalar The scalar value.
     * @return Vector2D The resulting vector.
     */
    template <
        typename ScalarT
      , typename = typename std::enable_if_t<std::is_arithmetic_v<ScalarT>, ScalarT>
    >
    Vector2D operator/(const ScalarT scalar) const
    {
      Vector2D temp(*this);
      temp /= scalar;
      return temp;
    }

    /**
     * @brief Compare if two vectors have different coordinates.
     * 
     * @param vector The rhs vector.
     * @return true The vectors have different coordinates.
     * @return false The vectors have same coordinates.
     */
    bool operator!=(const Vector2D& vector) const
    {
      if constexpr (std::is_floating_point_v<CoordinatesT>)
      {
        static constexpr float EPS = 10e-8f;
        return (std::fabs(this->x - vector.x) >= EPS || std::fabs(this->y - vector.y) >= EPS);
      }
      else
      {
        return (this->x != vector.x) || (this->y != vector.y);
      }
    }

    /**
     * @brief Compare if two vectors have same coordinates.
     * 
     * @param vector The rhs vector.
     * @return true The vectors have same coordinates.
     * @return false The vectors have different coordinates.
     */
    bool operator==(const Vector2D& vector) const
    {
      return !(*this != vector);
    }

    /**
     * @brief Compute the magnitude of the vector.
     * 
     * @return float The magnitude of the vector.
     */
    float abs() const
    {
      return std::sqrt(x * x + y * y);
    }

    /**
     * @brief Compute the phase of the vector.
     * 
     * @return float The phase of the vector, in radians.
     */
    float angle() const
    {
      return std::atan2(y, x);
    }

    /**
     * @brief Round the vector coordinates.
     * 
     * @return Vector2D Vector with rounded coordinates.
     */
    Vector2D rounded() const
    {
      Vector2D vector(*this);
      if constexpr (std::is_floating_point_v<CoordinatesT>)
      {
        vector.x = std::round(vector.x);
        vector.y = std::round(vector.y);
      }
      return vector;
    }

    /**
     * @brief Return the unit vector.
     * 
     * @return Vector2D The unit vector.
     */
    Vector2D<float> unit() const
    {
      Vector2D<float> unitVector{x, y};
      unitVector /= unitVector.abs();
      return unitVector;
    }
  };

  // aliases
  using Vector2Df = Vector2D<float>;
  using Vector2Di = Vector2D<int>;
}


#endif //EMBEDDED_GFX_VECTOR_2D_HPP