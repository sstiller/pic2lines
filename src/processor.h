#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "image.h"
#include "outputgenerator.h"

#include <string>
#include <memory>

class Processor
{
public:
  Processor(std::shared_ptr<const Image> inputImage,
            std::shared_ptr<OutputGenerator> outputGenerator);

  virtual ~Processor();

  virtual void run() = 0;

protected:
  std::shared_ptr<const Image> inputImage();
  std::shared_ptr<OutputGenerator> outputGenerator();
  double scale() const;

private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // PROCESSOR_H
