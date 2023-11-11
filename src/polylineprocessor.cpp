#include "polylineprocessor.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

// C
// TODO: REMOVE
#include <unistd.h>

//TODO: remove poly lines with only one point

#define BRIGHTNESS_INC 30
#define NEIGHBOUR_DIST 1 // TODO: if neighbour dist > 1, also increase brightness of pixels between
#define STOP_BRIGHTNESS 200.
#define START_OPACITY 1.
#define LINE_WIDTH 0.2
#define MIN_LINES_PER_POLY 5

PolyLineProcessor::PolyLineProcessor(const std::string inFilePath,
                                     std::shared_ptr<OutputGenerator> outputGenerator)
: Processor(inFilePath, outputGenerator)
{
  srand(time(nullptr));
  outputGenerator->setLineWidth(LINE_WIDTH);
}

void PolyLineProcessor::run()
{
  auto grayscaleImage = inputImage()->toGrayscale();

  double startBrightness{255};
  do
  {
    auto darkestPoint = findDarkest(grayscaleImage);
    startBrightness = *grayscaleImage.data(darkestPoint);
    auto currentBrightness = startBrightness;
    if(startBrightness > STOP_BRIGHTNESS)
    {
      break;
    }
    const auto startDarkness = 255. - startBrightness;
    auto currentDarkness = startDarkness;
    outputGenerator()->setOpacity(START_OPACITY * std::min(1., startDarkness / 255));
    std::vector<Point<double>> currentPolyLine;
    while(currentBrightness <= STOP_BRIGHTNESS
          && currentDarkness >= startDarkness * 0.7)
    {

      const auto randomX = (static_cast<double>(rand()) / RAND_MAX) * scale();
      const auto randomY = (static_cast<double>(rand()) / RAND_MAX) * scale();
      currentPolyLine.emplace_back(darkestPoint.x * scale() + randomX, darkestPoint.y * scale() + randomY);
      *grayscaleImage.data(darkestPoint) += static_cast<uint8_t>(BRIGHTNESS_INC);

      darkestPoint = findDarkest(grayscaleImage, darkestPoint, NEIGHBOUR_DIST);
      currentBrightness = *grayscaleImage.data(darkestPoint);
      currentDarkness = 255. - currentBrightness;
    }
    const double newOpcaity = std::min<double>(255., startDarkness);

    if(currentPolyLine.size() > MIN_LINES_PER_POLY + 1)
    {
      outputGenerator()->startPolyLine();
      for(const auto& currentPoint : currentPolyLine)
      {
        outputGenerator()->continuePolyLine(currentPoint);
      }
      outputGenerator()->endPolyLine();
    }
  } while(startBrightness < STOP_BRIGHTNESS);
}

Point<unsigned int> PolyLineProcessor::findDarkest(const Image& image)
{
  return findDarkest(image, {0, 0}, {image.width() - 1, image.height() - 1});
}

Point<unsigned int> PolyLineProcessor::findDarkest(const Image& image,
                                                   Point<unsigned int> topLeft,
                                                   Point<unsigned int> bottomRight)
{
//std::cout << __PRETTY_FUNCTION__ << "("
//          << topLeft.x << "/" << topLeft.y << " ; "
//          << bottomRight.x << "/" << bottomRight.y
//          << ")"<< std::endl;
  if(image.format() != Image::Format::GRAY8)
  {
    throw std::invalid_argument("PolyLineProcessor::findDarkest only supports GRAY8 images");
  }

  if(topLeft.x > bottomRight.x || topLeft.y > bottomRight.y)
  {
    throw std::logic_error("Points strange");
  }

  double darkestValue = 255;
  Point<unsigned int> darkestPoint;
  for(unsigned int x = topLeft.x; x <= bottomRight.x; x++)
  {
    for(unsigned int y = topLeft.y; y <= bottomRight.y; y++)
    {
      const Point currentPoint(x, y);
      // +/- 0.5 to avoid patterns (use random dark point if multiple with same brightness
      const double grayValue = *image.data(currentPoint) + (static_cast<double>(rand()) / RAND_MAX - 0.5);
      //std::cout << "rand = " << grayValue << std::endl;
      if(grayValue < darkestValue)
      {
        darkestValue = grayValue;
        if(darkestValue < 0.5)
        {
          return currentPoint;
        }
        darkestPoint = currentPoint;
      }
    }
  }

  return darkestPoint;
}

Point<unsigned int> PolyLineProcessor::findDarkest(const Image& image, Point<unsigned int> pos, unsigned int maxDistance)
{
  const Point<unsigned int> topLeft(std::clamp<int64_t>(static_cast<int64_t>(pos.x) - maxDistance, 0u, image.width() - 1),
                                    std::clamp<int64_t>(static_cast<int64_t>(pos.y) - maxDistance, 0u, image.height() - 1));
  const Point<unsigned int> bottomRight(std::clamp<int64_t>(static_cast<int64_t>(pos.x) + maxDistance, 0u, image.width() - 1 ),
                                        std::clamp<int64_t>(static_cast<int64_t>(pos.y) + maxDistance, 0u, image.height() - 1));

  return findDarkest(image, topLeft, bottomRight);
}
