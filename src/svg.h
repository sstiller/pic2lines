#ifndef SVG_H
#define SVG_H

#include "output.h"

class Svg final : public Output
{
public:
  Svg(const std::string& fileName,
      double width,
      double height,
      const std::string& unit = "mm");
  ~Svg();
public:
  // Output interface
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
