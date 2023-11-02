#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <memory>

class Output
{
protected:
  Output(double width, double height, const std::string& unit);
public:
  ~Output();

  double width() const;
  double height() const;
  std::string unit() const;

  // virtual functions
  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

  virtual void startPolyLine() = 0;
  virtual void continuePolyLine(double x, double y) = 0;
  virtual void endPolyLine() = 0;

private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // OUTPUT_H
