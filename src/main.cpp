
#include "svggenerator.hpp"
#include "gcodeoutputgenerator.hpp"
#include "pic2lines.hpp"
#include "gcodeconfig.hpp"

#include <iostream>
void printHelp(const std::string& command);

int main(int argc, char** argv)
{

  if(argc != 3)
  {
    printHelp(argv[0]);
    exit(EXIT_FAILURE);
  }

  //Pic2Lines pic2Lines(argv[1], std::make_shared<SvgGenerator>(argv[2], Dimensions<double>{100., 100.}, "mm"));

  GCodeConfig gCodeConfig;
  gCodeConfig.height() = 200;
  gCodeConfig.width() = 200;
  gCodeConfig.unit() = "mm";

  Pic2Lines pic2Lines(
    argv[1],
    std::make_shared<GCodeOutputGenerator>(
      argv[2],
      gCodeConfig
    )
  );

  return 0;
}


void printHelp(const std::string& command)
{
  std::cout << "Usage: " << command << " <jpegInFile> <ouputSvgFile>"
            << std::endl;
}
