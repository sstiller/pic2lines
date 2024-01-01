#include "gcodeoutputgenerator.hpp"

#include <stdexcept>

#include <iostream>

class PolyLine : public std::vector<Point<double>>
{
public:
  const uint8_t power{0};
  PolyLine(uint8_t power)
  : power{power}
  {
  }
};

class GCodeOutputGenerator::Private
{
public:
  std::vector<PolyLine> polyLines;
  GCodeConfig config;

  Private(const GCodeConfig& config)
  : config(config)
  {
  }
  void sortLines()
  {
    //use vector.swap for sorting
    /* start with first
     * while current entry != last
     * find closest first / last
     * if last, reverse vector
     * swap second with closest
     * continue with second line
     */

    for(unsigned int i = 0; i < polyLines.size() - 1 ; i++)
    {
      auto& currentLine = polyLines.at(i);
      const auto& lastPoint = currentLine.back(); // last point of the (poly)line
      double minDist = std::numeric_limits<double>::max();
      unsigned int nearestIndex = i + 1;
      bool nearestIsBack{false};
      for(unsigned int j = i + 1; j < polyLines.size(); j++)
      {
        auto& nextLine = polyLines.at(j);
        auto currentDistance = std::abs((lastPoint - nextLine.front()).length());
        if(currentDistance < minDist)
        {
          minDist = currentDistance;
          nearestIndex = j;
          nearestIsBack = false;
        }
        currentDistance = std::abs((lastPoint - nextLine.back()).length());
        if(currentDistance < minDist)
        {
          minDist = currentDistance;
          nearestIndex = j;
          nearestIsBack = true;
        }
      }
      // revert if back
      if(nearestIsBack)
      {

        std::reverse(polyLines.at(nearestIndex).begin(), polyLines.at(nearestIndex).end());
      }
      // may the next be the nearest
      polyLines.at(i + 1).swap(polyLines.at(nearestIndex));
    }
  }
};


// https://marlinfw.org/docs/gcode/G000-G001.html

GCodeOutputGenerator::GCodeOutputGenerator(const std::string &fileName,
                                           const GCodeConfig &config)
: TextFileOutputGenerator(fileName, config)
, prv{std::make_unique<Private>(config)}
{
  laserOff();
  appendOutput("G90\n"); // absolute positioning
  setUnit(unit());
}

GCodeOutputGenerator::~GCodeOutputGenerator()
{
  prv->sortLines();
  generate();
}

void GCodeOutputGenerator::updateLineProperties()
{
  // nothing to do, laser strength set using opacity()
}

void GCodeOutputGenerator::drawLine(const Point<double>& p1, const Point<double>& p2)
{
  PolyLine line(opacity() * 255);
  line.push_back(p1);
  line.push_back(p2);
  prv->polyLines.push_back(line);
}

void GCodeOutputGenerator::drawPolyline(const std::vector<Point<double> >& points)
{
  if(points.size() < 2)
  {
    throw std::invalid_argument("polyline needs at least 2 points");
  }

  PolyLine line(opacity() * 255);
  std::copy(points.begin(), points.end(), std::back_inserter(line));
  prv->polyLines.push_back(line);
}

void GCodeOutputGenerator::setUnit(const std::string &unit)
{
  if(unit == "mm")
  {
    appendOutput("G21\n");
  }
  else if(unit == "in")
  {
    appendOutput("G20\n");
  }
  else
  {
    throw std::invalid_argument("Unknown unit, only 'mm and 'in' supported");
  }
}

void GCodeOutputGenerator::generate()
{
  for(const auto& line : prv->polyLines)
  {
    generateLine(line.power, line);
  }

  laserOff();
}

void GCodeOutputGenerator::generateLine(uint8_t power, const std::vector<Point<double> >& points)
{
  // TODO: do not move if same point
  if(points.size() < 2)
  {
    throw std::invalid_argument("polyline needs at least 2 points");
  }

  setSpeed(prv->config.travelSpeed());
  moveTo(points.front());

  laserOn(power);
  setSpeed(prv->config.burningSpeed());
  // start at the 2nd point because we already are at the first one
  for(unsigned int i = 1; i < points.size(); i++)
  {
    moveTo(points.at(i));
  }
  laserOn(0);
}

void GCodeOutputGenerator::laserOff()
{
  appendOutput(prv->config.laserOffCommand() + " S0\n");
}

void GCodeOutputGenerator::laserOn(uint8_t strength)
{
  appendOutput(prv->config.laserOnCommand() + " S" + std::to_string(static_cast<int>(strength)) + "\n");
}

void GCodeOutputGenerator::setSpeed(double speed)
{
  appendOutput("G1 F" + std::to_string(speed) + "\n");
}

void GCodeOutputGenerator::moveTo(const Point<double> point)
{
  appendOutput("G1 X" + std::to_string(point.x) + " Y" + std::to_string(point.y) + "\n");
}

