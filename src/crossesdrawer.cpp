#include "crossesdrawer.hpp"

CrossesDrawer::CrossesDrawer(std::shared_ptr<const Image> inputImage,
                                   std::shared_ptr<OutputGenerator> outputGenerator)
: Drawer(inputImage, outputGenerator)
{
}

void CrossesDrawer::run()
{
  outputGenerator()->setLineWidth(scale() / 5);
  auto grayscaleImage = inputImage()->toGrayscale();
  const auto imageDimensions = grayscaleImage->dimensions();
  for(int y = 0; y < imageDimensions.y; y++)
  {
    for(int x = 0; x < imageDimensions.x; x++)
    {
      const uint8_t grayValue = *grayscaleImage->data(Point<int>{x, y});

      const auto pixelTopLeft = Point<double>{static_cast<double>(x), static_cast<double>(y)} * scale();

      if(grayValue < 192)
      {
        // top left to right bottom of pixel
        outputGenerator()->drawLine(pixelTopLeft, pixelTopLeft + Dimensions<double>{scale(), scale()});
      }
      if(grayValue < 95)
      {
        // top bottom to right top of pixel
        outputGenerator()->drawLine(pixelTopLeft + Dimensions<double>{0., scale()},
                                    pixelTopLeft + Dimensions<double>{scale(), 0.});
      }
      if(grayValue < 48)
      {
        // vertical
        outputGenerator()->drawLine(pixelTopLeft + Dimensions<double>{scale() / 2, 0},
                                    pixelTopLeft + Dimensions<double>{scale() / 2, scale()});
      }
      if(grayValue < 24)
      {
        // horizontal
        outputGenerator()->drawLine(pixelTopLeft + Dimensions<double>{0, scale() / 2},
                                    pixelTopLeft + Dimensions<double>{scale(), scale() / 2});
      }
    }
  }
}
