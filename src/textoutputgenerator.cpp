#include "textoutputgenerator.hpp"

#include <fstream>

class TextOutputGenerator::Private
{
public:
  std::string fileContent;
};

TextOutputGenerator::TextOutputGenerator(const OutputConfig& config)
: OutputGenerator(config)
, prv{std::make_unique<Private>()}
{
}

TextOutputGenerator::~TextOutputGenerator() = default;

const std::string& TextOutputGenerator::getOutput()
{
  return prv->fileContent;
}

void TextOutputGenerator::appendOutput(std::string data)
{
  prv->fileContent.append(data);
}

void TextOutputGenerator::writeToFile(const std::string& fileName)
{
  std::ofstream outFile(fileName, std::ofstream::out);
  outFile << prv->fileContent;
  outFile.close();
}
