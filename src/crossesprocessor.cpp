#include "crossesprocessor.h"

CrossesProcessor::CrossesProcessor(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator)
: Processor(inFilePath, outputGenerator)
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

      if(grayValue < 192)
      {
        outputGenerator()->drawLine(x * scale(), y * scale(), x * scale() + scale(), y * scale() + scale());
      }
      if(grayValue < 95)
      {
        outputGenerator()->drawLine(x * scale(), y * scale() + scale(), x * scale() + scale(), y * scale());
      }
      if(grayValue < 48)
      {
        outputGenerator()->drawLine(x * scale() + scale() / 2, y * scale() , x * scale() + scale() / 2, y * scale() + scale());
      }
      if(grayValue < 24)
      {
        outputGenerator()->drawLine(x * scale(), y * scale() + scale() / 2, x * scale() + scale(), y * scale() + scale() / 2);
      }
    }
  }
}
