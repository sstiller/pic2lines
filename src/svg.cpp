#include "svg.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

class Svg::Private
{
public:
  std::string svgStroke{"stroke:#000000;stroke-opacity:1;stroke-width:0.1"};
  struct
  {
    double width{0.1};
    double opacity{1.0};
  }currentLineProperties;
};


Svg::Svg(const std::string& fileName, const Dimensions<double>& dimensions, const std::string& unit)
: TextFileOutputGenerator(fileName, dimensions, unit)
, prv{std::make_unique<Private>()}
{
  startFile();
}

Svg::~Svg()
{
  finishFile();
}

void Svg::updateLineProperties()
{
  prv->svgStroke = "stroke:#000000;stroke-opacity:" + std::to_string(opacity());
  prv->svgStroke += ";stroke-width:" + std::to_string(lineWidth());
}

void Svg::drawLine(double x1, double y1, double x2, double y2)
{
  appendOutput(std::string(2, ' '));
  appendOutput("<line style=\"" + prv->svgStroke + "\" "
                          + "x1=\"" + std::to_string(x1) + "\" "
                          + "y1=\"" + std::to_string(y1) + "\" "
                          + "x2=\"" + std::to_string(x2) + "\" "
                          + "y2=\"" + std::to_string(y2) + "\" />\n");
}

void Svg::drawPolyline(const std::vector<Point<double> >& points)
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

void Svg::startFile()
{
  appendOutput("<svg viewBox=\"0 0 " + std::to_string(dimensions().x) + " " + std::to_string(dimensions().y) + "\"\n"
                          + "  units=\"" + unit() + "\"\n"
                          + "  width=\"" + std::to_string(dimensions().x) + unit() + "\"\n"
                          + "  height=\"" + std::to_string(dimensions().y) + unit()+ "\"\n"
                          + "  xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void Svg::finishFile()
{
  appendOutput("</svg>\n");
}

