// local includes
#include "gui.hpp"

#include "drawerfactory.hpp"
#include "gcodeconfig.hpp"
#include "gcodeoutputgenerator.hpp"
#include "jpeg.hpp"
#include "svggenerator.hpp"

// libs
#include <spdlog/spdlog.h>

// C
#include <cassert>

Gui::Gui() = default;

Gui::~Gui() = default;

// static
std::vector<std::string> Gui::availableDrawers()
{
  return DrawerFactory::availableDrawers();
}

std::shared_ptr<OutputGenerator> Gui::getPreviewOutputGenerator()
{
  spdlog::warn("{}(): No override. Returning empty pointer.", __func__);
  return {};
}

void Gui::generatePreview(std::shared_ptr<const Image> inputImage,
                          const std::string& drawerName)
{
  auto drawer = DrawerFactory::create(drawerName);
  auto previewOutputGenerator = getPreviewOutputGenerator();
  if(! previewOutputGenerator)
  {
    spdlog::warn("{}(): No preview generator available", __func__);
    return;
  }
  drawer->process(inputImage, getPreviewOutputGenerator());
}

std::vector<std::string> Gui::availableOutputGenerators()
{
  return {"gcode", "svg"};
}

void Gui::generateOutput(std::shared_ptr<const Image> inputImage,
                         const std::string& drawerName,
                         const std::string& outputGeneratorName,
                         const std::string& outFilePath)
{
  assert(inputImage.operator bool());
  assert(! drawerName.empty());
  assert(! outputGeneratorName.empty());
  assert(! outFilePath.empty());

  auto drawer = DrawerFactory::create(drawerName);

  auto createOutputGenerator =
    [&outputGeneratorName]() -> std::shared_ptr<OutputGenerator>
    {
      spdlog::warn("createOutputGenerator lambbda: TODO: make a factory and a better way to configure.");

      if(outputGeneratorName == "gcode")
      {
        GCodeConfig gCodeConfig;
        gCodeConfig.height() = 200;
        gCodeConfig.width() = 200;
        gCodeConfig.unit() = "mm";

        return std::make_shared<GCodeOutputGenerator>(gCodeConfig);
      }
      else if(outputGeneratorName == "svg")
      {
        OutputConfig svgConfig;
        svgConfig.height() = 100;
        svgConfig.width() = 100;
        svgConfig.unit() = "mm";

        return std::make_shared<SvgGenerator>(svgConfig);
      }
      else
      {
        throw std::invalid_argument("Invalid outputGeneratorName: " + outputGeneratorName);
      }
    };

  auto outputGenerator = createOutputGenerator();
  drawer->process(inputImage, outputGenerator);
  outputGenerator->writeToFile(outFilePath);
}

std::shared_ptr<Image> Gui::readInputJpeg(const std::string& path)
{
  return readJpeg(path); // throws on error
}


