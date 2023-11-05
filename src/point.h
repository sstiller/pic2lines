#ifndef POINT_H
#define POINT_H

template <typename T = unsigned int>
class Point
{
public:
  T x;
  T y;

  Point(T x = 0, T y = 0)
  : x{x}
  , y{y}
  {
  }
};

#endif // POINT_H
