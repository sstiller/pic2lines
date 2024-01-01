#ifndef PIC2LINES_HPP
#define PIC2LINES_HPP

#include "outputgenerator.hpp"

#include <string>
#include <memory>

class Pic2Lines final
{
public:
  Pic2Lines(const std::string& inFilePath,
            std::shared_ptr<OutputGenerator> outputGenerator,
            const std::string& outFilePath);
  ~Pic2Lines();
private:
  class Private;
  std::unique_ptr<Private> prv;};

#endif // PIC2LINES_HPP
