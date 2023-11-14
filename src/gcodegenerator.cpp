#include "gcodegenerator.h"

#include <stdexcept>

#define LASER_OFF std::string("M05")
#define LASER_ON std::string("M04")

// units / min
#define TRAVEL_SPEED 3000
#define BURNING_SPEED 1000

//class GCodeGenerator::Private
//{
//public:
//};


// https://marlinfw.org/docs/gcode/G000-G001.html

GCodeGenerator::GCodeGenerator(const std::string& fileName,
                               const Dimensions<double>& dimensions,
                               const std::string& unit)
: TextFileOutputGenerator(fileName, dimensions, unit)
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
  laserOff();
}

void GCodeGenerator::updateLineProperties()
{

}

void GCodeGenerator::drawLine(const Point<double>& p1, const Point<double>& p2)
{
  setSpeed(TRAVEL_SPEED);
  moveTo(p1);

  setSpeed(BURNING_SPEED);
  laserOn(opacity() * 255);
  moveTo(p2);
  laserOn(0);
}

void GCodeGenerator::drawPolyline(const std::vector<Point<double> >& points)
{
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

