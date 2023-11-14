#ifndef POLYLINEPROCESSOR_H
#define POLYLINEPROCESSOR_H

#include "processor.h"
#include "vec2.h"

class PolyLineProcessor : public Processor
{
public:
  PolyLineProcessor(std::shared_ptr<const Image> inputImage,
                    std::shared_ptr<OutputGenerator> outputGenerator);

  // Processor interface
public:
  void run() override;

private:
  static Point<int> findDarkest(const Image& image);
  static Point<int> findDarkest(const Image& image, Point<int> topLeft, Point<int> bottomRight);
  static Point<int> findDarkest(const Image& image, Point<int> pos, unsigned int maxDistance);
};

#endif // POLYLINEPROCESSOR_H
