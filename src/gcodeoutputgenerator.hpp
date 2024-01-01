#ifndef GCODEOUTPUTGENERATOR_HPP
#define GCODEOUTPUTGENERATOR_HPP

#include "textoutputgenerator.hpp"
#include "gcodeconfig.hpp"

#include <cstdint>
#include <memory>
#include <string>

class GCodeOutputGenerator final : public TextOutputGenerator
{
public:
  GCodeOutputGenerator(const GCodeConfig& config);
  ~GCodeOutputGenerator();

  // OutputGenerator interface
public:
  void updateLineProperties() override;
  void drawLine(const Point<double>& p1, const Point<double>& p2) override;
  void drawPolyline(const std::vector<Point<double> >& points) override;


private:
  class Private;
  std::unique_ptr<Private> prv;

  void setUnit(const std::string& unit);
  void generate();
  void generateLine(uint8_t power, const std::vector<Point<double> >& points);
  void laserOff();
  void laserOn(uint8_t strength);
  void setSpeed(double speed);
  void moveTo(const Point<double> point);
};

#endif // GCODEOUTPUTGENERATOR_HPP
