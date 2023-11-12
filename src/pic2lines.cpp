#include "pic2lines.h"
#include "outputgenerator.h"
#include "crossesprocessor.h"
#include "polylineprocessor.h"

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
      throw std::invalid_argument("no valid outut generator");
    }
  }
};

Pic2Lines::~Pic2Lines() = default;

Pic2Lines::Pic2Lines(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator)
{
  //CrossesProcessor (inFilePath, outputGenerator).run();
  PolyLineProcessor(inFilePath, outputGenerator).run();

}

