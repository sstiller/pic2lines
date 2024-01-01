#ifndef DRAWER_H
#define DRAWER_H

#include "image.hpp"
#include "outputgenerator.hpp"

#include <string>
#include <memory>

class Drawer
{
public:
  Drawer(std::shared_ptr<const Image> inputImage,
            std::shared_ptr<OutputGenerator> outputGenerator);

  virtual ~Drawer();

  virtual void run() = 0;

protected:
  std::shared_ptr<const Image> inputImage();
  std::shared_ptr<OutputGenerator> outputGenerator();
  double scale() const;

private:
  class Private;
  std::unique_ptr<Private> prv;
};


#endif // DRAWER_H
