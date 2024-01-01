#include "pic2lines.hpp"
#include "outputgenerator.hpp"

#include "crossesdrawer.hpp"
#include "polylinedrawer.hpp"

#include "jpeg.hpp"

#include <spdlog/spdlog.h>

#include <stdexcept>

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

Pic2Lines::Pic2Lines(const std::string& inFilePath,
                     std::shared_ptr<OutputGenerator> outputGenerator,
                     const std::string& outFilePath)
{
  auto inputImage = readJpeg(inFilePath); // throws on error
  spdlog::info("Loaded image: {} {}",
               inputImage->dimensions().toString(),
               Image::formatToString(inputImage->format()));

  //CrossesDrawer(inputImage, outputGenerator).run();
  //CrossesDrawer(inputImage->verticalFlip(), outputGenerator).run();
  PolyLineDrawer(inputImage->verticalFlip(), outputGenerator).run();
  //PolyLineDrawer(inputImage, outputGenerator).run();
//#error use vflip when gcode

  outputGenerator->writeToFile(outFilePath);
}


