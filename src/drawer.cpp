#include "drawer.h"

#include <iostream>

class Drawer::Private
{
public:
  std::shared_ptr<const Image> inputImage;
  std::shared_ptr<OutputGenerator> outputGenerator;
  double scale{1};

  Private(std::shared_ptr<const Image> inputImage,
          std::shared_ptr<OutputGenerator> outputGenerator)
  : inputImage{inputImage}
  , outputGenerator{outputGenerator}
  {
    if(! inputImage)
    {
      throw std::invalid_argument("Processor: No valid image");
    }

  }
};

Drawer::Drawer(std::shared_ptr<const Image> inputImage,
                     std::shared_ptr<OutputGenerator> outputGenerator)
: prv{std::make_unique<Private>(inputImage, outputGenerator)}
{
  const auto xScale = outputGenerator->dimensions().x / inputImage->dimensions().x;
  const auto yScale = outputGenerator->dimensions().y / inputImage->dimensions().y;
  prv->scale = std::min(xScale, yScale);
}

Drawer::~Drawer() = default;

std::shared_ptr<const Image> Drawer::inputImage()
{
  return prv->inputImage;
}

std::shared_ptr<OutputGenerator> Drawer::outputGenerator()
{
  return prv->outputGenerator;
}

double Drawer::scale() const
{
  return prv->scale;
}
