#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include "vec2.hpp"
#include "outputconfig.hpp"

#include <memory>
#include <string>
#include <vector>

class OutputGenerator
{
protected:
  OutputGenerator(const Dimensions<double> dim, const std::string& unit);
  OutputGenerator(const OutputConfig& config);
public:
  ~OutputGenerator();

  Dimensions<double> dimensions() const;
  std::string unit() const;


//#error function to process whole polyline., class Point
  void setLineWidth(double width) ;
  double lineWidth() const;

  void setOpacity(double opacity);
  double opacity() const;

  // virtual functions
  virtual void updateLineProperties() = 0;

  virtual void drawLine(const Point<double>& p1, const Point<double>& p2) = 0;
  virtual void drawPolyline(const std::vector<Point<double>>& points) = 0;


private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // OUTPUTGENERATOR_H