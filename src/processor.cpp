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
  std::cout << "Loaded image: " << prv->inputImage->width() << "x" << prv->inputImage->height()
            << " " << Image::formatToString(prv->inputImage->format())
            << std::endl;

  const auto xScale = outputGenerator->width() / prv->inputImage->width();
  const auto yScale = outputGenerator->height() / prv->inputImage->height();
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
