
#include "svggenerator.hpp"
#include "gcodeoutputgenerator.hpp"
#include "pic2lines.hpp"
#include "gcodeconfig.hpp"

#include <spdlog/spdlog.h>

#include <iostream>

void printHelp(const std::string& command);

int main(int argc, char** argv)
{

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  if(argc != 3)
  {
    printHelp(argv[0]);
    exit(EXIT_FAILURE);
  }

  const std::string inputFilename(argv[1]);
  const std::string outputFilename(argv[2]);

#if 1
  OutputConfig svgConfig;
  svgConfig.height() = 100;
  svgConfig.width() = 100;
  svgConfig.unit() = "mm";

  Pic2Lines pic2Lines(
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
    inputFilename,
    std::make_shared<GCodeOutputGenerator>(gCodeConfig),
    outputFilename
  );
#endif

  return 0;
}


void printHelp(const std::string& command)
{
  std::cout << "Usage: " << command << " <jpegInFile> <ouputFile>"
            << std::endl;
}
