#ifndef TEXTFILEOUTPUTGENERATOR_HPP
#define TEXTFILEOUTPUTGENERATOR_HPP

#include "outputconfig.hpp"
#include "outputgenerator.hpp"

#include <memory>

class TextFileOutputGenerator : public OutputGenerator
{
public:
  TextFileOutputGenerator(const std::string& fileName, const OutputConfig& config);
  ~TextFileOutputGenerator();
protected:
  void appendOutput(std::string data);

private:
  class Private;
  std::unique_ptr<Private> prv;
};

#endif // TEXTFILEOUTPUTGENERATOR_HPP
