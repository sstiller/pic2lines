#include "polylinedrawer.hpp"

#include <spdlog/spdlog.h>

#include <stdexcept>

// C
// TODO: REMOVE
#include <unistd.h>

//TODO: remove poly lines with only one point

//TODO: replace by PolyLineDrawer::Config, inherits from DrawerConfig
#define BRIGHTNESS_INC 25
#define NEIGHBOUR_DIST 1 // TODO: if neighbour dist > 1, also increase brightness of pixels between
#define STOP_BRIGHTNESS 200.
#define START_OPACITY 1.
#define LINE_WIDTH 0.2
#define MIN_LINES_PER_POLY 5

void PolyLineDrawer::doProcess(std::shared_ptr<const Image> inputImage,
                               std::shared_ptr<OutputGenerator> outputGenerator)
{
  srand(time(nullptr));
  outputGenerator->setLineWidth(LINE_WIDTH);

  auto grayscaleImage = inputImage->toGrayscale();
  const auto scalingFactor = calculateScalingFactor(inputImage->dimensions(),
                                                    outputGenerator->dimensions());

  double startBrightness{255};
  do
  {
    auto darkestPoint = findDarkest(*grayscaleImage);
    startBrightness = *grayscaleImage->data(darkestPoint);
    auto currentBrightness = startBrightness;
    if(startBrightness > STOP_BRIGHTNESS)
    {
      break;
    }
    const auto startDarkness = 255. - startBrightness;
    auto currentDarkness = startDarkness;
    outputGenerator->setOpacity(START_OPACITY * std::min(1., startDarkness / 255));
    std::vector<Point<double>> currentPolyLine;
    while(currentBrightness <= STOP_BRIGHTNESS
          && currentDarkness >= startDarkness * 0.7)
    {
      const auto randomX = (static_cast<double>(rand()) / RAND_MAX) * scalingFactor;
      const auto randomY = (static_cast<double>(rand()) / RAND_MAX) * scalingFactor;
      currentPolyLine.emplace_back(Point<double>{darkestPoint.x * scalingFactor + randomX, darkestPoint.y * scalingFactor + randomY});
      *grayscaleImage->data(darkestPoint) += static_cast<uint8_t>(BRIGHTNESS_INC);

      darkestPoint = findDarkest(*grayscaleImage, darkestPoint, NEIGHBOUR_DIST);
      currentBrightness = *grayscaleImage->data(darkestPoint);
      currentDarkness = 255. - currentBrightness;
    }

    if(currentPolyLine.size() > MIN_LINES_PER_POLY + 1)
    {
      outputGenerator->drawPolyline(currentPolyLine);
    }
  } while(startBrightness < STOP_BRIGHTNESS);
}

Point<int> PolyLineDrawer::findDarkest(const Image& image)
{
  return findDarkest(image, {0, 0}, {image.dimensions() - Dimensions<int>{1, 1}});
}

Point<int> PolyLineDrawer::findDarkest(const Image& image,
                                          Point<int> topLeft,
                                          Point<int> bottomRight)
{
  spdlog::trace("{}({}/{}; {}/{})", topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
  if(image.format() != Image::Format::GRAY8)
  {
    throw std::invalid_argument("PolyLineProcessor::findDarkest only supports GRAY8 images");
  }

  if(topLeft.x > bottomRight.x || topLeft.y > bottomRight.y)
  {
    throw std::logic_error("Points strange");
  }

  double darkestValue = 255;
  Point<int> darkestPoint;
  for(int x = topLeft.x; x <= bottomRight.x; x++)
  {
    for(int y = topLeft.y; y <= bottomRight.y; y++)
    {
      const Point<int> currentPoint{x, y};
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

Point<int> PolyLineDrawer::findDarkest(const Image& image, Point<int> pos, unsigned int maxDistance)
{
  const Dimensions<int> delta{static_cast<int>(maxDistance), static_cast<int>(maxDistance)};
  const auto topLeft = (pos - delta).clamp({0, 0}, {image.dimensions() - Dimensions<int>{1, 1}});
  const auto bottomRight = (pos + delta).clamp({0, 0}, {image.dimensions() - Dimensions<int>{1, 1}});

  return findDarkest(image, topLeft, bottomRight);
}
