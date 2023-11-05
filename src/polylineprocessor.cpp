#include "polylineprocessor.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

// C
// TODO: REMOVE
#include <unistd.h>

//TODO: remove poly lines with only one point

#define BRIGHTNESS_INC 10
#define NEIGHBOUR_DIST 1 // TODO: if neighbour dist > 1, also increase brightness of pixels between
#define STOP_BRIGHTNESS 150

PolyLineProcessor::PolyLineProcessor(const std::string inFilePath,
                                     std::shared_ptr<OutputGenerator> outputGenerator)
: Processor(inFilePath, outputGenerator)
{
  srand(time(nullptr));
  outputGenerator->setLineWidth(0.05);
}

void PolyLineProcessor::run()
{
  auto grayscaleImage = inputImage()->toGrayscale();

  uint8_t startBrightness{255};
  do
  {
    auto darkestPoint = findDarkest(grayscaleImage);
    startBrightness = *grayscaleImage.data(darkestPoint);
    auto currentBrightness = startBrightness;
    if(startBrightness > STOP_BRIGHTNESS)
    {
      break;
    }
    outputGenerator()->startPolyLine();

    while(currentBrightness <= STOP_BRIGHTNESS)
    {
      const auto randomX = (static_cast<double>(rand()) / RAND_MAX) * scale();
      const auto randomY = (static_cast<double>(rand()) / RAND_MAX) * scale();
      Point<double>outputPoint(darkestPoint.x * scale() + randomX, darkestPoint.y * scale() + randomY);
      outputGenerator()->continuePolyLine(outputPoint);
      *grayscaleImage.data(darkestPoint) = std::min<int64_t>(255, static_cast<int64_t>(currentBrightness) + BRIGHTNESS_INC);

      darkestPoint = findDarkest(grayscaleImage, darkestPoint, NEIGHBOUR_DIST);
      currentBrightness = *grayscaleImage.data(darkestPoint);
    }
    outputGenerator()->endPolyLine();
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
  for(unsigned int x = topLeft.x; x < bottomRight.x; x++)
  {
    for(unsigned int y = topLeft.y; y < bottomRight.y; y++)
    {
      const Point currentPoint(x, y);
      const double grayValue = *image.data(currentPoint);
      if(grayValue < darkestValue)
      {

        darkestValue = grayValue;
        if(darkestValue == 0)
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
