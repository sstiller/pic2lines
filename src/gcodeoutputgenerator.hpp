#ifndef GCODEOUTPUTGENERATOR_H
#define GCODEOUTPUTGENERATOR_H

#include "textfileoutputgenerator.hpp"

#include <cstdint>
#include <memory>
#include <string>

class GCodeOutputGenerator final : public TextFileOutputGenerator
{
public:
  GCodeOutputGenerator(const std::string& fileName,
                       const Dimensions<double>& dimensions,
                       const std::string& unit = "mm");
  ~GCodeOutputGenerator();

  // OutputGenerator interface
public:
  void updateLineProperties() override;
  void drawLine(const Point<double>& p1, const Point<double>& p2) override;
  void drawPolyline(const std::vector<Point<double> >& points) override;


private:
  class Private;
  std::unique_ptr<Private> prv;

  void generate();
  void generateLine(uint8_t power, const std::vector<Point<double> >& points);
  void laserOff();
  void laserOn(uint8_t strength);
  void setSpeed(double speed);
  void moveTo(const Point<double> point);
};

#endif // GCODEOUTPUTGENERATOR_H
