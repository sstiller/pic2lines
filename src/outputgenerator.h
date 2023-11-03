#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

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

  // virtual functions
  virtual void setLineWidth(double width) = 0;

  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

  virtual void startPolyLine() = 0;
  virtual void continuePolyLine(double x, double y) = 0;
  virtual void endPolyLine() = 0;

private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // OUTPUTGENERATOR_H
