
#include "svggenerator.h"
#include "gcodeoutputgenerator.h"
#include "pic2lines.h"

#include <iostream>
void printHelp(const std::string& command);

int main(int argc, char** argv)
{

  if(argc != 3)
  {
    printHelp(argv[0]);
    exit(EXIT_FAILURE);
  }

  Pic2Lines pic2Lines(argv[1], std::make_shared<SvgGenerator>(argv[2], Dimensions<double>{100., 100.}, "mm"));
  //Pic2Lines pic2Lines(argv[1], std::make_shared<GCodeGenerator>(argv[2], Dimensions<double>{100., 100.}, "mm"));

  return 0;
}


void printHelp(const std::string& command)
{
  std::cout << "Usage: " << command << " <jpegInFile> <ouputSvgFile>"
            << std::endl;
}
