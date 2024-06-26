#ifndef TEXTOUTPUTGENERATOR_H
#define TEXTOUTPUTGENERATOR_H

#include "outputconfig.hpp"
#include "outputgenerator.hpp"

#include <memory>

class TextOutputGenerator : public OutputGenerator
{
public:
  explicit TextOutputGenerator(const OutputConfig& config);
  ~TextOutputGenerator();

  [[nodiscard]] const std::string& getOutput();
protected:
  void appendOutput(std::string data);

private:
  class Private;
  std::unique_ptr<Private> prv;

  // OutputGenerator interface
public:
  void writeToFile(const std::string& fileName) override;
  void init() override;
};

#endif // TEXTOUTPUTGENERATOR_H
