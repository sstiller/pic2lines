#ifndef POLYLINEDRAWER_HPP
#define POLYLINEDRAWER_HPP

#include "drawer.hpp"
#include "vec2.hpp"

class PolyLineDrawer : public Drawer
{
public:
  PolyLineDrawer(std::shared_ptr<const Image> inputImage,
                    std::shared_ptr<OutputGenerator> outputGenerator);

  // Processor interface
public:
  void run() override;

private:
  static Point<int> findDarkest(const Image& image);
  static Point<int> findDarkest(const Image& image, Point<int> topLeft, Point<int> bottomRight);
  static Point<int> findDarkest(const Image& image, Point<int> pos, unsigned int maxDistance);
};

#endif // POLYLINEDRAWER_HPP
