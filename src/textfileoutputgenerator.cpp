#include "textfileoutputgenerator.h"

#include <fstream>

class TextFileOutputGenerator::Private
{
public:
  const std::string fileName;
  std::string fileContent;
  Private(const std::string& fileName)
  : fileName{fileName}
  {
  }
};

TextFileOutputGenerator::TextFileOutputGenerator(const std::string& fileName, const Dimensions<double>& dimensions, const std::string& unit)
: OutputGenerator(dimensions, unit)
, prv{std::make_unique<Private>(fileName)}
{
}

TextFileOutputGenerator::~TextFileOutputGenerator()
{
  std::ofstream outFile(prv->fileName, std::ofstream::out);
  outFile << prv->fileContent;
  outFile.close();
}

void TextFileOutputGenerator::appendOutput(std::string data)
{
  prv->fileContent.append(data);
}
