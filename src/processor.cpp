#include "processor.h"
#include "jpeg.h"

#include <iostream>

class Processor::Private
{
public:
  std::shared_ptr<const Image> inputImage;
  std::shared_ptr<OutputGenerator> outputGenerator;
  double scale{1};

  Private(std::shared_ptr<OutputGenerator> outputGenerator)
  : outputGenerator{outputGenerator}
  {
  }
};

Processor::Processor(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator)
: prv{std::make_unique<Private>(outputGenerator)}
{
  prv->inputImage = readJpeg(inFilePath); // throws on error
  std::cout << "Loaded image: " << prv->inputImage->dimensions().toString()
            << " " << Image::formatToString(prv->inputImage->format())
            << std::endl;

  const auto xScale = outputGenerator->dimensions().x / prv->inputImage->dimensions().x;
  const auto yScale = outputGenerator->dimensions().y / prv->inputImage->dimensions().y;
  prv->scale = std::min(xScale, yScale);
}

Processor::~Processor() = default;

std::shared_ptr<const Image> Processor::inputImage()
{
  return prv->inputImage;
}

std::shared_ptr<OutputGenerator> Processor::outputGenerator()
{
  return prv->outputGenerator;
}

double Processor::scale() const
{
  return prv->scale;
}
