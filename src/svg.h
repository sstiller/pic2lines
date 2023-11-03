#ifndef SVG_H
#define SVG_H

#include "outputgenerator.h"


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

class Svg final : public OutputGenerator
{
public:
  Svg(const std::string& fileName,
      double width,
      double height,
      const std::string& unit = "mm");
  ~Svg();
public:
  // Output interface
  void setLineWidth(double width) override;
  void drawLine(double x1, double y1, double x2, double y2) override;
  void startPolyLine() override;
  void continuePolyLine(double x, double y) override;
  void endPolyLine() override;

private:
  class Private;
  std::unique_ptr<Private> prv;

  void startFile();
  void finishFile();

};

#endif // SVG_H
