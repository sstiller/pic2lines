#include "svg.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>

class Svg::Private
{
public:
  const std::string fileName;
  std::string fileContent;
  std::vector<std::string> currentOutputElements;
  std::string svgStroke{"stroke:#000000;stroke-opacity:1;stroke-width:0.1"};
  Private(const std::string& fileName)
  : fileName{fileName}
  {
  }
};


Svg::Svg(const std::string& fileName, double width, double height, const std::string& unit)
: OutputGenerator(width, height, unit)
, prv{std::make_unique<Private>(fileName)}
{
  startFile();
}

Svg::~Svg()
{
  finishFile();
}

void Svg::setLineWidth(double width)
{
  prv->svgStroke = "stroke:#000000;stroke-opacity:1;stroke-width:" + std::to_string(width);
}

void Svg::drawLine(double x1, double y1, double x2, double y2)
{
  if(prv->currentOutputElements.empty()
     || prv->currentOutputElements.back() != "svg")
  {
    throw std::logic_error("Failed drawing line, not in element \"svg\"");
  }

  prv->fileContent.append(prv->currentOutputElements.size() * 2, ' ');
  prv->fileContent.append("<line style=\"" + prv->svgStroke + "\" "
                          + "x1=\"" + std::to_string(x1) + "\" "
                          + "y1=\"" + std::to_string(y1) + "\" "
                          + "x2=\"" + std::to_string(x2) + "\" "
                          + "y2=\"" + std::to_string(y2) + "\" />\n");
}

void Svg::startPolyLine()
{
  if(prv->currentOutputElements.empty()
     || prv->currentOutputElements.back() != "svg")
  {
    throw std::logic_error("Failed starting polyline, not in element \"svg\"");
  }
  prv->fileContent.append(prv->currentOutputElements.size() * 2, ' ');
  prv->fileContent.append("<polyline style=\"" + prv->svgStroke + ";fill:none\" points=\"");
  prv->currentOutputElements.emplace_back("polyline");
}

void Svg::continuePolyLine(double x, double y)
{
  if(prv->currentOutputElements.empty()
     || prv->currentOutputElements.back() != "polyline")
  {
    throw std::logic_error("Failed continuing polyline, not in element \"polyline\"");
  }

  prv->fileContent.append(std::to_string(x) + "," + std::to_string(y) + " ");
}

void Svg::endPolyLine()
{
  if(prv->currentOutputElements.empty()
     || prv->currentOutputElements.back() != "polyline")
  {
    throw std::logic_error("Failed finishing polyline, not in element \"polyline\"");
  }

  prv->fileContent.append("\" />\"\n");
  prv->currentOutputElements.pop_back();
}

void Svg::startFile()
{
  if(!prv->currentOutputElements.empty())
  {
    throw std::logic_error("File already started");
  }
  prv->fileContent.append("<svg viewBox=\"0 0 " + std::to_string(width()) + " " + std::to_string(height()) + "\"\n"
                          + "  units=\"" + unit() + "\"\n"
                          + "  width=\"" + std::to_string(width()) + unit() + "\"\n"
                          + "  height=\"" + std::to_string(height()) + unit()+ "\"\n"
                          + "  xmlns=\"http://www.w3.org/2000/svg\">\n");
  prv->currentOutputElements.emplace_back("svg");
}

void Svg::finishFile()
{
  if(prv->currentOutputElements.empty()
     || prv->currentOutputElements.back() != "svg")
  {
    throw std::logic_error("Finishing SVG failed, not in element \"svg\"");
  }
  prv->currentOutputElements.pop_back();
  prv->fileContent.append("</svg>\n");

  std::ofstream outFile(prv->fileName, std::ofstream::out);
  outFile << prv->fileContent;
  outFile.close();
}

