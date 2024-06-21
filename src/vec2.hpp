#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <string>
#include <algorithm>

template <typename T = double>
class Vec2
{
public:
  T x{0};
  T y{0};

  [[nodiscard]] T length() const
  {
    return std::sqrt(x * x + y * y);
  }

  Vec2<T> operator- (const Vec2<T>& other) const
  {
    return {x - other.x, y - other.y};
  }
  Vec2<T>& operator-= (const Vec2<T>& other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2<T> operator+ (const Vec2<T>& other) const
  {
    return {x + other.x, y + other.y};
  }

  Vec2<T>& operator+= (const Vec2<T>& other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2<T> operator* (T val) const
  {
    return {x * val, y * val};
  }

  Vec2<T>& operator*= (T val)
  {
    x *= val;
    y *= val;
    return *this;
  }

  Vec2<T> operator/ (T val) const
  {
    return {x / val, y / val};
  }

  Vec2<T>& operator/= (T val)
  {
    x /= val;
    y /= val;
    return *this;
  }

  [[nodiscard]] T area() const
  {
    return x * y;
  }

  [[nodiscard]] std::string toString() const
  {
    return "(" + std::to_string(x) + "x" + std::to_string(y) + ")";
  }

  [[nodiscard]] Vec2<T> clamp(const Vec2<T>& lower, const Vec2<T>& upper) const
  {
     return {std::clamp(x, lower.x, upper.x),
             std::clamp(y, lower.y, upper.y)
            };
  }

};

template <typename T>
using Dimensions = Vec2<T>;

template <typename T>
using Point = Vec2<T>;

#endif // VEC2_HPP
