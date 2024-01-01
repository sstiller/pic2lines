#include "pic2lines.hpp"
#include "outputgenerator.hpp"

#include "crossesdrawer.hpp"
#include "polylinedrawer.hpp"

#include "jpeg.hpp"

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
      throw std::invalid_argument("no valid output generator");
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

  //CrossesDrawer(inputImage, outputGenerator).run();
  //CrossesDrawer(inputImage->verticalFlip(), outputGenerator).run();
  PolyLineDrawer(inputImage->verticalFlip(), outputGenerator).run();
  //PolyLineDrawer(inputImage, outputGenerator).run();
//#error use vflip when gcode
}

