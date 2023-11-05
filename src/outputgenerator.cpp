#include "outputgenerator.h"

#include <stdexcept>

class OutputGenerator::Private
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

OutputGenerator::OutputGenerator(double width, double height, const std::string& unit)
: prv{std::make_unique<Private>(width, height, unit)}
{
}

OutputGenerator::~OutputGenerator() = default;

double OutputGenerator::width() const
{
  return prv->width;
}

double OutputGenerator::height() const
{
  return prv->height;
}

std::string OutputGenerator::unit() const
{
  return prv->unit;
}

void OutputGenerator::drawLine(Point<double> p1, Point<double> p2)
{
  drawLine(p1.x, p1.y, p2.x, p2.y);
}

void OutputGenerator::continuePolyLine(Point<double> point)
{
  continuePolyLine(point.x, point.y);
}


