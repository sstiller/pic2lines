#include "crossesdrawer.hpp"

void CrossesDrawer::doProcess(std::shared_ptr<const Image> inputImage,
                              std::shared_ptr<OutputGenerator> outputGenerator)
{
  const auto scalingFactor = calculateScalingFactor(inputImage->dimensions(),
                                                    outputGenerator->dimensions());
  outputGenerator->setLineWidth(scalingFactor / 5);
  auto grayscaleImage = inputImage->toGrayscale();
  const auto imageDimensions = grayscaleImage->dimensions();
  for(int y = 0; y < imageDimensions.y; y++)
  {
    for(int x = 0; x < imageDimensions.x; x++)
    {
      const uint8_t grayValue = *grayscaleImage->data(Point<int>{x, y});

      const auto pixelTopLeft = Point<double>{static_cast<double>(x), static_cast<double>(y)} * scalingFactor;

      if(grayValue < 192)
      {
        // top left to right bottom of pixel
        outputGenerator->drawLine(pixelTopLeft, pixelTopLeft + Dimensions<double>{scalingFactor, scalingFactor});
      }
      if(grayValue < 95)
      {
        // top bottom to right top of pixel
        outputGenerator->drawLine(pixelTopLeft + Dimensions<double>{0., scalingFactor},
                                    pixelTopLeft + Dimensions<double>{scalingFactor, 0.});
      }
      if(grayValue < 48)
      {
        // vertical
        outputGenerator->drawLine(pixelTopLeft + Dimensions<double>{scalingFactor / 2, 0},
                                    pixelTopLeft + Dimensions<double>{scalingFactor / 2, scalingFactor});
      }
      if(grayValue < 24)
      {
        // horizontal
        outputGenerator->drawLine(pixelTopLeft + Dimensions<double>{0, scalingFactor / 2},
                                    pixelTopLeft + Dimensions<double>{scalingFactor, scalingFactor / 2});
      }
    }
  }
}
