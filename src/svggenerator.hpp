#ifndef SVGGENERATOR_H
#define SVGGENERATOR_H

#include "textfileoutputgenerator.hpp"

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

  void drawLine(const Point<double>& p1, const Point<double>& p2) override;
  void drawPolyline(const std::vector<Point<double> >& points) override;

private:
  class Private;
  std::unique_ptr<Private> prv;

  void startFile();
  void finishFile();


};

#endif // SVGGENERATOR_H
