#ifndef CROSSESPROCESSOR_H
#define CROSSESPROCESSOR_H

#include "processor.h"

class CrossesProcessor : public Processor
{
public:
  CrossesProcessor(const std::string inFilePath, std::shared_ptr<OutputGenerator> outputGenerator);

  // Processor interface
public:
  void run() override;
};

#endif // CROSSESPROCESSOR_H
