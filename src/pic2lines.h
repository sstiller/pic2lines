#ifndef PIC2LINES_H
#define PIC2LINES_H

#include "output.h"

#include <string>
#include <memory>

class Pic2Lines final
{
public:
  Pic2Lines(const std::string inFile, std::shared_ptr<Output> output);
  ~Pic2Lines();
private:
  class Private;
  std::unique_ptr<Private> prv;};

#endif // PIC2LINES_H
