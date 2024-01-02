#include "pic2lines.hpp"
#include "outputgenerator.hpp"
//#include "crossesdrawer.hpp"
//#include "polylinedrawer.hpp"
#include "drawerfactory.hpp"
#include "jpeg.hpp"

#include <spdlog/spdlog.h>

#include <stdexcept>


Pic2Lines::Pic2Lines(const std::string& drawerType,
                     const std::string& inFilePath,
                     std::shared_ptr<OutputGenerator> outputGenerator,
                     const std::string& outFilePath)
{
  auto inputImage = readJpeg(inFilePath); // throws on error
  spdlog::info("requested drawer: {}", drawerType);
  spdlog::info("Loaded image {}: {} {}",
               inFilePath,
               inputImage->dimensions().toString(),
               Image::formatToString(inputImage->format()));

  auto drawer = DrawerFactory::create(drawerType);

//#error use vflip when gcode
  drawer->process(inputImage, outputGenerator);
  //CrossesDrawer().process(inputImage, outputGenerator);
  //CrossesDrawer().process(inputImage->verticalFlip(), outputGenerator);
  //PolyLineDrawer().process(inputImage->verticalFlip(), outputGenerator);
  //PolyLineDrawer().process(inputImage, outputGenerator);

  outputGenerator->writeToFile(outFilePath);
}


