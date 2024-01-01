#ifndef SVGGENERATOR_HPP
#define SVGGENERATOR_HPP

#include "outputconfig.hpp"
#include "textfileoutputgenerator.hpp"

class SvgGenerator final : public TextFileOutputGenerator
{
public:
  SvgGenerator(const std::string& fileName, const OutputConfig &config);
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

#endif // SVGGENERATOR_HPP
