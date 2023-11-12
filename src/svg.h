#ifndef SVG_H
#define SVG_H

#include "textfileoutputgenerator.h"


// example code
//  outputGenerator->startPolyLine();
//  outputGenerator->continuePolyLine(10, 10);
//  outputGenerator->continuePolyLine(10, 20);
//  outputGenerator->continuePolyLine(20, 20);
//  outputGenerator->continuePolyLine(20, 10);
//  outputGenerator->continuePolyLine(10, 10);
//  outputGenerator->endPolyLine();
//
//  outputGenerator->drawLine(10, 10, 20, 20);

class Svg final : public TextFileOutputGenerator
{
public:
  Svg(const std::string& fileName,
      const Dimensions<double>& dimensions,
      const std::string& unit = "mm");
  ~Svg();
public:
  // Output interface
  void updateLineProperties() override;

  void drawLine(double x1, double y1, double x2, double y2) override;
  void drawPolyline(const std::vector<Point<double> >& points);

private:
  class Private;
  std::unique_ptr<Private> prv;

  void startFile();
  void finishFile();


};

#endif // SVG_H
