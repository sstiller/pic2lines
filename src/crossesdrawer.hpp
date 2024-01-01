#ifndef CROSSESDRAWER_HPP
#define CROSSESDRAWER_HPP

#include "drawer.hpp"

class CrossesDrawer : public Drawer
{
public:
  CrossesDrawer(std::shared_ptr<const Image> inputImage,
                   std::shared_ptr<OutputGenerator> outputGenerator);

  // Processor interface
public:
  void run() override;
};

#endif // CROSSESDRAWER_HPP
