#include "outputgenerator.hpp"

#include <algorithm>
#include <stdexcept>

class OutputGenerator::Private
{
public:
  const Dimensions<double> dimensions;
  const std::string unit;
  double lineWidth{1};
  double opacity{1};

  Private(Dimensions<double> dimensions, const std::string& unit)
  : dimensions{dimensions}
  , unit{unit}
  {
    if(dimensions.area() == 0 || unit.empty())
    {
      throw std::invalid_argument("Dimensions or unit invalid");
    }
  }
};

OutputGenerator::OutputGenerator(const OutputConfig& config)
: prv{std::make_unique<Private>(Dimensions<double>{config.width(), config.height()},
                                config.unit())}
{

}

OutputGenerator::~OutputGenerator() = default;

Dimensions<double> OutputGenerator::dimensions() const
{
  return prv->dimensions;
}

std::string OutputGenerator::unit() const
{
  return prv->unit;
}

void OutputGenerator::setLineWidth(double width)
{
  prv->lineWidth = std::max(0., width);
  updateLineProperties();
}

double OutputGenerator::lineWidth() const
{
  return prv->lineWidth;
}

void OutputGenerator::setOpacity(double opacity)
{
  prv->opacity = std::clamp(opacity, 0., 1.);
//std::cout << __func__ << "(): " << opacity << "->" << prv->opacity << std::endl;
  updateLineProperties();
}

double OutputGenerator::opacity() const
{
  return prv->opacity;
}


