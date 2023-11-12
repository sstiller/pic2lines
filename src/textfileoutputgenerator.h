#ifndef TEXTFILEOUTPUTGENERATOR_H
#define TEXTFILEOUTPUTGENERATOR_H

#include "drawing.h"
#include "outputgenerator.h"

#include <memory>

class TextFileOutputGenerator : public OutputGenerator
{
public:
  TextFileOutputGenerator(const std::string& fileName, const Dimensions<double>& dimensions, const std::string& unit);
  ~TextFileOutputGenerator();
protected:
  void appendOutput(std::string data);

private:
  class Private;
  std::unique_ptr<Private> prv;
};

#endif // TEXTFILEOUTPUTGENERATOR_H
