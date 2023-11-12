#ifndef SVGGENERATOR_H
#define SVGGENERATOR_H

#include "textfileoutputgenerator.h"

class SvgGenerator final : public TextFileOutputGenerator
{
public:
  SvgGenerator(const std::string& fileName,
      const Dimensions<double>& dimensions,
      const std::string& unit = "mm");
  ~SvgGenerator();
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

#endif // SVGGENERATOR_H
