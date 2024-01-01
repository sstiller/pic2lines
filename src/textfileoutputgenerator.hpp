#ifndef TEXTFILEOUTPUTGENERATOR_H
#define TEXTFILEOUTPUTGENERATOR_H

#include "vec2.hpp"
#include "outputgenerator.hpp"

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
