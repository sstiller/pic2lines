#ifndef CROSSESDRAWER_HPP
#define CROSSESDRAWER_HPP

#include "drawer.hpp"

class CrossesDrawer : public Drawer
{
protected:
  void doProcess(std::shared_ptr<const Image> inputImage,
               std::shared_ptr<OutputGenerator> outputGenerator) override;
};

#endif // CROSSESDRAWER_HPP
