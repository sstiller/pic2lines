#include "output.h"

#include <stdexcept>

class Output::Private
{
public:
  double width;
  double height;
  const std::string unit;
  Private(double width, double height, const std::string& unit)
  : width{width}
  , height{height}
  , unit{unit}
  {
    if(! (width > 0 && height > 0 && ! unit.empty()))
    {
      throw std::invalid_argument("Dimensions or unit not correct");
    }
  }
};

Output::Output(double width, double height, const std::string& unit)
: prv{std::make_unique<Private>(width, height, unit)}
{
}

Output::~Output() = default;

double Output::width() const
{
  return prv->width;
}

double Output::height() const
{
  return prv->height;
}

std::string Output::unit() const
{
  return prv->unit;
}


