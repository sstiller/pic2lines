#ifndef TEXTOUTPUTGENERATOR_H
#define TEXTOUTPUTGENERATOR_H

#include "outputconfig.hpp"
#include "outputgenerator.hpp"

#include <memory>

class TextOutputGenerator : public OutputGenerator
{
public:
  TextOutputGenerator(const OutputConfig& config);
  ~TextOutputGenerator();

  const std::string& getOutput();
protected:
  void appendOutput(std::string data);

private:
  class Private;
  std::unique_ptr<Private> prv;


  // OutputGenerator interface
public:
  void writeToFile(const std::string& fileName) override;
};

#endif // TEXTOUTPUTGENERATOR_H
