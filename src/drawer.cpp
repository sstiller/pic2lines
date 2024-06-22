#include "drawer.hpp"

Drawer::~Drawer() = default;

void Drawer::process(
  std::shared_ptr<const Image> inputImage,
  std::shared_ptr<OutputGenerator> outputGenerator
)
{
  outputGenerator->init();
  doProcess(inputImage, outputGenerator);
  outputGenerator->finish();
}

double Drawer::calculateScalingFactor(
  const Dimensions<int>& imageDimensions,
  const Dimensions<double>& outputDimension
)
{
  const auto xScale = outputDimensions.x / imageDimensions.x;
  const auto yScale = outputDimensions.y / imageDimensions.y;
  return std::min(xScale, yScale);
}


