#define USE_GUI

#ifdef USE_GUI
  #include "gui/fltkgui.hpp"
  #include <thread>
#else
  #include "svggenerator.hpp"
  #include "gcodeoutputgenerator.hpp"
  #include "pic2lines.hpp"
  #include "gcodeconfig.hpp"
  #include "drawerfactory.hpp"
#endif

#include <spdlog/spdlog.h>

#include <iostream>
#include <numeric> // accumulate


void printHelp(const std::string& command);

int main(int argc, char** argv)
{

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
#ifdef USE_GUI

  spdlog::info("Starting event loop thread");

  std::shared_ptr<Gui> gui = std::make_shared<FltkGui>();
  std::thread guiEventThread(
    [gui, argc, argv]()
    {
      gui->runEventLoop(argc, argv);
    }
  );

  spdlog::info("Waiting for event loop thread to quit");
  guiEventThread.join();
#else
  if(argc != 3)
  {
    printHelp(argv[0]);
    exit(EXIT_FAILURE);
  }

  const std::string inputFilename(argv[1]);
  const std::string outputFilename(argv[2]);

  const auto drawerNames = DrawerFactory::availableDrawers();
  // Creating a string separated by commas
  const std::string drawerNamesString = std::accumulate(
    std::next(drawerNames.begin()), drawerNames.end(), drawerNames.front(),
      [](const std::string &a, const std::string &b) {
        return a + ", " + b;
      }
  );
  spdlog::info("Available drawers: {}", drawerNamesString);
#if 1
  const std::string drawerType = "polyline";
#else
  const std::string drawerType = "crosses";
#endif

#if 0
  OutputConfig svgConfig;
  svgConfig.height() = 100;
  svgConfig.width() = 100;
  svgConfig.unit() = "mm";

  Pic2Lines pic2Lines(
    drawerType,
    inputFilename,
    std::make_shared<SvgGenerator>(svgConfig),
    outputFilename
  );
#else
  GCodeConfig gCodeConfig;
  gCodeConfig.height() = 200;
  gCodeConfig.width() = 200;
  gCodeConfig.unit() = "mm";

  Pic2Lines pic2Lines(
    drawerType,
    inputFilename,
    std::make_shared<GCodeOutputGenerator>(gCodeConfig),
    outputFilename
  );
#endif
#endif // USE_GUI

  spdlog::info("{} quits" , argv[0]);

  return 0;
}


void printHelp(const std::string& command)
{
  std::cout << "Usage: " << command << " <jpegInFile> <ouputFile>"
            << std::endl;
}
