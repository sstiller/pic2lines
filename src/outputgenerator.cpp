#include "outputgenerator.h"

#include <algorithm>
#include <stdexcept>

class OutputGenerator::Private
{
public:
  double width;
  double height;
  const std::string unit;
  double lineWidth{1};
  double opacity{1};

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


