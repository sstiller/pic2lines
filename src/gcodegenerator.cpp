#include "gcodegenerator.h"

#include <stdexcept>

#define LASER_OFF std::string("M05")
#define LASER_ON std::string("M04")

// units / min
#define TRAVEL_SPEED 3000
#define BURNING_SPEED 1000


#include <iostream>


class GCodeGenerator::Private
{
public:
  std::vector<std::vector<Point<double>>> polyLines;

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

GCodeGenerator::GCodeGenerator(const std::string& fileName,
                               const Dimensions<double>& dimensions,
                               const std::string& unit)
: TextFileOutputGenerator(fileName, dimensions, unit)
, prv{std::make_unique<Private>()}
{
  laserOff();
  appendOutput("G90\n");
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

GCodeGenerator::~GCodeGenerator()
{
  prv->sortLines();
  generate();
}

void GCodeGenerator::updateLineProperties()
{
  // nothing to do, laser strength set using opacity()
}

void GCodeGenerator::drawLine(const Point<double>& p1, const Point<double>& p2)
{
  prv->polyLines.push_back({p1, p2});
}

void GCodeGenerator::drawPolyline(const std::vector<Point<double> >& points)
{
  if(points.size() < 2)
  {
    throw std::invalid_argument("polyline needs at least 2 points");
  }

  prv->polyLines.push_back(points);
}

void GCodeGenerator::generate()
{
  for(const auto line : prv->polyLines)
  {
    generateLine(line);
  }

  laserOff();
}

void GCodeGenerator::generateLine(const std::vector<Point<double> >& points)
{
  // TODO: do not move if same point
  if(points.size() < 2)
  {
    throw std::invalid_argument("polyline needs at least 2 points");
  }

  setSpeed(TRAVEL_SPEED);
  moveTo(points.front());

  laserOn(opacity() * 255);
  setSpeed(BURNING_SPEED);
  // start at the 2nd point because we already are at the first one
  for(int i = 1; i < points.size(); i++)
  {
    moveTo(points.at(i));
  }
  laserOn(0);
}

void GCodeGenerator::laserOff()
{
  appendOutput(LASER_OFF+ " S0\n");
}

void GCodeGenerator::laserOn(uint8_t strength)
{
  appendOutput(LASER_ON + " S" + std::to_string(static_cast<int>(strength)) + "\n");
}

void GCodeGenerator::setSpeed(double speed)
{
  appendOutput("G1 F" + std::to_string(speed) + "\n");
}

void GCodeGenerator::moveTo(const Point<double> point)
{
  appendOutput("G1 X" + std::to_string(point.x) + " Y" + std::to_string(point.y) + "\n");
}

