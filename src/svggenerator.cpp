#include "svggenerator.hpp"

#include <stdexcept>
#include <vector>

class SvgGenerator::Private
{
public:
  std::string svgStroke{"stroke:#000000;stroke-opacity:1;stroke-width:0.1"};
  struct
  {
    double width{0.1};
    double opacity{1.0};
  }currentLineProperties;
};


SvgGenerator::SvgGenerator(const OutputConfig& config)
: TextOutputGenerator(config)
, prv{std::make_unique<Private>()}
{
  init();
}

SvgGenerator::~SvgGenerator() = default;

void SvgGenerator::updateLineProperties()
{
  prv->svgStroke = "stroke:#000000;stroke-opacity:" + std::to_string(opacity());
  prv->svgStroke += ";stroke-width:" + std::to_string(lineWidth());
}

void SvgGenerator::drawLine(const Point<double>& p1, const Point<double>& p2)
{
  appendOutput(std::string(2, ' '));
  appendOutput("<line style=\"" + prv->svgStroke + "\" "
                          + "x1=\"" + std::to_string(p1.x) + "\" "
                          + "y1=\"" + std::to_string(p1.y) + "\" "
                          + "x2=\"" + std::to_string(p2.x) + "\" "
                          + "y2=\"" + std::to_string(p2.y) + "\" />\n");
}

void SvgGenerator::drawPolyline(const std::vector<Point<double> >& points)
{
  if(points.size() < 2)
  {
    throw std::invalid_argument("Less than 2 points in poly line");
  }
  appendOutput(std::string(2, ' '));
  appendOutput("<polyline style=\"" + prv->svgStroke + ";fill:none\" points=\"");

  for(const auto& currentPoint : points)
  {
    appendOutput(std::to_string(currentPoint.x) + "," + std::to_string(currentPoint.y) + " ");
  }
  appendOutput("\" />\"\n");
}

void SvgGenerator::init()
{
  TextOutputGenerator::init();

  appendOutput("<svg viewBox=\"0 0 " + std::to_string(dimensions().x) + " " + std::to_string(dimensions().y) + "\"\n"
                          + "  units=\"" + unit() + "\"\n"
                          + "  width=\"" + std::to_string(dimensions().x) + unit() + "\"\n"
                          + "  height=\"" + std::to_string(dimensions().y) + unit()+ "\"\n"
                          + "  xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void SvgGenerator::finish()
{
  appendOutput("</svg>\n");
}

