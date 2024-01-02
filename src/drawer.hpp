#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "outputgenerator.hpp"
#include "image.hpp"

#include <string>
#include <memory>

class Drawer
{
public:
  void process(std::shared_ptr<const Image> inputImage,
               std::shared_ptr<OutputGenerator> outputGenerator);

protected:
  virtual void doProcess(std::shared_ptr<const Image> inputImage,
                         std::shared_ptr<OutputGenerator> outputGenerator) = 0;

  static double calculateScalingFactor(const Dimensions<int>& imageDimensions,
                                       const Dimensions<double>& outputDimensions);
};


#endif // DRAWER_HPP
