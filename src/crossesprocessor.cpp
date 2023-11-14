#include "crossesprocessor.h"

CrossesProcessor::CrossesProcessor(std::shared_ptr<const Image> inputImage,
                                   std::shared_ptr<OutputGenerator> outputGenerator)
: Processor(inputImage, outputGenerator)
{
}

void CrossesProcessor::run()
{
  outputGenerator()->setLineWidth(scale() / 5);
  auto input = inputImage();
  const auto imageDimensions = input->dimensions();
  for(int y = 0; y < imageDimensions.y; y++)
  {
    for(int x = 0; x < imageDimensions.x; x++)
    {
      const auto* point = input->data(Point<int>{x, y});
      unsigned int grayValue{0};
      for(unsigned int componentIdx = 0; componentIdx < Image::formatBpp(input->format()); componentIdx++)
      {
        grayValue += point[componentIdx];
      }
      grayValue /= Image::formatBpp(input->format());

      const auto pixelTopLeft = Point<double>{static_cast<double>(x), static_cast<double>(y)} * scale();

      if(grayValue < 192)
      {
        // top left to right bottom of pixel
        outputGenerator()->drawLine(pixelTopLeft, pixelTopLeft + Dimensions<double>{scale(), scale()});
      }
      if(grayValue < 95)
      {
        // top bottom to right top of pixel
        outputGenerator()->drawLine(pixelTopLeft + Dimensions<double>{scale(), -scale()},
                                    pixelTopLeft + Dimensions<double>{-scale(), scale()});
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
