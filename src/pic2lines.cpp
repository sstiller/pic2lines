#include "pic2lines.h"
#include "outputgenerator.h"

#include "crossesprocessor.h"
#include "polylineprocessor.h"

#include "jpeg.h"

#include <stdexcept>
#include <iostream>

class Pic2Lines::Private
{
public:
  std::shared_ptr<OutputGenerator> outputGenerator;
  Private(std::shared_ptr<OutputGenerator> output)
  : outputGenerator{output}
  {
    if(! outputGenerator)
    {
      throw std::invalid_argument("no valid outut generator");
    }
  }
};

Pic2Lines::~Pic2Lines() = default;

Pic2Lines::Pic2Lines(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator)
{

  auto inputImage = readJpeg(inFilePath); // throws on error
  std::cout << "Loaded image: " << inputImage->dimensions().toString()
            << " " << Image::formatToString(inputImage->format())
            << std::endl;

  //CrossesProcessor(inputImage, outputGenerator).run();
  CrossesProcessor(inputImage->verticalFlip(), outputGenerator).run();
  //PolyLineProcessor(inputImage->verticalFlip(), outputGenerator).run();
  //PolyLineProcessor(inputImage, outputGenerator).run();
//#error use vflip when gcode
}

