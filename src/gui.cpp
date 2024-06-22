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

Gui::Gui()
{
  selectedOutputGenerator = availableOutputGenerators().front();
}

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

void Gui::generatePreview(std::shared_ptr<const Image> inputImage)
{
  if(selectedDrawer.empty())
  {
    spdlog::warn("{}(): No drawer selected", __func__);
    return;
  }
  const auto drawer = DrawerFactory::create(selectedDrawer);
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

void Gui::generateOutput(const std::string& outFilePath)
{

  try
  {
    if(selectedInputImagePath.empty())
    {
      throw std::logic_error("no image selected");
    }

    if(selectedDrawer.empty())
    {
      throw std::invalid_argument("no drawer selected");
    }

    if(selectedOutputGenerator.empty())
    {
      throw std::invalid_argument("no output generator selected");
    }

    if(outFilePath.empty())
    {
      throw std::invalid_argument("target file selected");
    }

    const auto inputImage = readInputJpeg(selectedInputImagePath);

    const auto drawer = DrawerFactory::create(selectedDrawer);

    auto createOutputGenerator =
      [this]() -> std::shared_ptr<OutputGenerator>
      {
        spdlog::warn("createOutputGenerator lambbda: TODO: make a factory and a better way to configure.");

        if(selectedOutputGenerator == "gcode")
        {
          GCodeConfig gCodeConfig;
          gCodeConfig.height() = 200;
          gCodeConfig.width() = 200;
          gCodeConfig.unit() = "mm";

          return std::make_shared<GCodeOutputGenerator>(gCodeConfig);
        }
        else if(selectedOutputGenerator == "svg")
        {
          OutputConfig svgConfig("svg");
          svgConfig.height() = 100;
          svgConfig.width() = 100;
          svgConfig.unit() = "mm";

          return std::make_shared<SvgGenerator>(svgConfig);
        }
        else
        {
          throw std::invalid_argument("Invalid outputGeneratorName: " + selectedOutputGenerator);
        }
      };

    const auto outputGenerator = createOutputGenerator();
    drawer->process(inputImage, outputGenerator);
    outputGenerator->writeToFile(outFilePath);
  }
  catch(const std::exception& exc)
  {
    displayErrorMessage(exc.what());
  }
}

std::shared_ptr<Image> Gui::readInputJpeg(const std::string& path)
{
  return readJpeg(path); // throws on error
}


