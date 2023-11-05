#ifndef POLYLINEPROCESSOR_H
#define POLYLINEPROCESSOR_H

#include "processor.h"
#include "point.h"

class PolyLineProcessor : public Processor
{
public:
  PolyLineProcessor(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator);

  // Processor interface
public:
  void run() override;

private:
  static Point<unsigned int> findDarkest(const Image& image);
  static Point<unsigned int> findDarkest(const Image& image, Point<unsigned int> topLeft, Point<unsigned int> bottomRight);
  static Point<unsigned int> findDarkest(const Image& image, Point<unsigned int> pos, unsigned int maxDistance);
};

#endif // POLYLINEPROCESSOR_H
