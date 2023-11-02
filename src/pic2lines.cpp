#include "pic2lines.h"
#include "jpeg.h"

#include <stdexcept>
#include <iostream>

class Pic2Lines::Private
{
public:
  std::shared_ptr<Output> output;
  Private(std::shared_ptr<Output> output)
  : output{output}
  {
    if(! output)
    {
      throw std::invalid_argument("no valid outut generator");
    }
  }
};


Pic2Lines::Pic2Lines(const std::string inFile, std::shared_ptr<Output> output)
{

  const auto image = readJpeg(inFile);

  std::cout << "Loaded image: " << image->width() << "x" << image->height()
            << " " << Image::formatToString(image->format())
            << std::endl;


  const auto xScale = output->width() / image->width();
  const auto yScale = output->height() / image->height();
  const auto scale = std::min(xScale, yScale);

  for(unsigned int y = 0; y < image->height(); y++)
  {
    for(unsigned int x = 0; x < image->width(); x++)
    {
      const auto* point = image->data(x, y);
      unsigned int grayValue{0};
      for(unsigned int componentIdx = 0; componentIdx < Image::formatBpp(image->format()); componentIdx++)
      {
        grayValue += point[componentIdx];
      }
      grayValue /= Image::formatBpp(image->format());
      std::cout << (grayValue >= 127 ? "#" : " ");

      if(grayValue < 127)
      {
        output->drawLine(x * scale, y * scale, x * scale + scale, y * scale + scale);
        output->drawLine(x * scale, y * scale + scale, x * scale + scale, y * scale);
      }

    }
    std::cout << std::endl;
  }
  // test code until we can load an image
  std::cout << __PRETTY_FUNCTION__ << ": TODO: open file or better take bitmap image data in ctor"
            << std::endl;

//  output->startPolyLine();
//  output->continuePolyLine(10, 10);
//  output->continuePolyLine(10, 20);
//  output->continuePolyLine(20, 20);
//  output->continuePolyLine(20, 10);
//  output->continuePolyLine(10, 10);
//  output->endPolyLine();

//  output->drawLine(10, 10, 20, 20);
}

Pic2Lines::~Pic2Lines() = default;
