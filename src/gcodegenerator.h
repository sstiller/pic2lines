#ifndef GCODEGENERATOR_H
#define GCODEGENERATOR_H

#include "textfileoutputgenerator.h"

#include <cstdint>
#include <memory>
#include <string>

class GCodeGenerator final : public TextFileOutputGenerator
{
public:
  GCodeGenerator(const std::string& fileName,
                 const Dimensions<double>& dimensions,
                 const std::string& unit = "mm");
  ~GCodeGenerator();

  // OutputGenerator interface
public:
  void updateLineProperties() override;
  void drawLine(const Point<double>& p1, const Point<double>& p2) override;
  void drawPolyline(const std::vector<Point<double> >& points) override;


private:
//  class Private;
//  std::unique_ptr<Private> prv;

  void laserOff();
  void laserOn(uint8_t strength);
  void setSpeed(double speed);
  void moveTo(const Point<double> point);


};

#endif // GCODEGENERATOR_H
