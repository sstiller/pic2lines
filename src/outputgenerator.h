#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include "point.h"

#include <string>
#include <memory>

class OutputGenerator
{
protected:
  OutputGenerator(double width, double height, const std::string& unit);
public:
  ~OutputGenerator();

  double width() const;
  double height() const;
  std::string unit() const;

  void drawLine(Point<double> p1, Point <double> p2);
  void continuePolyLine(Point<double> point);


  void setLineWidth(double width) ;
  double lineWidth() const;

  void setOpacity(double opacity);
  double opacity() const;

  // virtual functions
  virtual void updateLineProperties() = 0;

  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

  virtual void startPolyLine() = 0;
  virtual void continuePolyLine(double x, double y) = 0;
  virtual void endPolyLine() = 0;

private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // OUTPUTGENERATOR_H
