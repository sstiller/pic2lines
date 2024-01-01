#include "image.hpp"

#include <stdexcept>
#include <cmath>

class Image::Private
{
public:
  const Image::Format format;
  Dimensions<int> dimensions;
  std::vector<uint8_t> data;

  Private(Image::Format format, const Dimensions<int>& dimensions)
  : format{format}
  , dimensions{dimensions}
  , data(Image::formatBpp(format) * dimensions.x * dimensions.y)
  {
  }
};

Image::Image(Format format, const Dimensions<int>& dimensions)
: prv{std::make_unique<Private>(format, dimensions)}
{
  if(! dimensions.length())
  {
    throw std::invalid_argument("Image < 1 pixel in at least one dimension");
  }
}

Image::Image(const Image& other)
: prv {std::make_unique<Private>(*other.prv)}
{
}

Image::~Image() = default;

Dimensions<int> Image::dimensions() const
{
  return prv->dimensions;
}


Image::Format Image::format() const
{
  return prv->format;
}

uint8_t* Image::data(const Point<int>& point)
{
  // point within image?
  if((prv->dimensions - point).area() <= 0)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((point.y * prv->dimensions.x + point.x) * formatBpp(prv->format));
}

const uint8_t* Image::data(const Point<int>& point) const
{
  // point within image?
  if((prv->dimensions - point).area() <= 0)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((point.y * prv->dimensions.x + point.x) * formatBpp(prv->format));
}


std::shared_ptr<Image> Image::toGrayscale() const
{
  switch(prv->format)
  {
    case Format::GRAY8:
    {
      return std::make_shared<Image>(*this);
    }
    case Format::RGB24:
    {
      auto  ret = std::make_shared<Image>(Format::GRAY8, prv->dimensions);
      const auto bytesPerPixel = formatBpp(prv->format);
      for(unsigned int i = 0; i < prv->dimensions.x * prv->dimensions.y; i++)
      {
        ret->prv->data[i] = static_cast<uint8_t>(
          prv->data[i * bytesPerPixel] * 0.299 // red
          + prv->data[i * bytesPerPixel + 1] * 0.587 // green
          + prv->data[i * bytesPerPixel + 2] * 0.114 // blue
        );
      }
      return ret;
    }
  }
}

std::shared_ptr<Image> Image::verticalFlip() const
{
  auto ret = std::make_shared<Image>(format(), prv->dimensions);
  for(int y = 0; y < prv->dimensions.y; y++)
  {
    const auto srcY = (prv->dimensions.y - y) - 1;
    std::copy(data(Point<int>{0, srcY}),
              data(Point<int>{prv->dimensions.x - 1, srcY}) + 1,
              ret->data(Point<int>{0, y})
             );
  }
  return ret;
}


unsigned int Image::formatBpp(Format format)
{
  switch(format)
  {
    case Format::GRAY8:
    {
      return 1;
    }
    case Format::RGB24:
    {
      return 3;
    }
  }
}

std::string Image::formatToString(Format format)
{
  switch(format)
  {
    case Format::GRAY8:
    {
      return "GRAY8";
    }
    case Format::RGB24:
    {
      return "RGB24";
    }
  }
}

Point<int> Image::indexToPosition(int index) const
{
  index /= formatBpp(prv->format);
  const auto bytesPerPixel = formatBpp(prv->format);
  Point<int> ret{(index % prv->dimensions.x) * static_cast<int>(bytesPerPixel) /*x*/,
                          (index / prv->dimensions.x) * static_cast<int>(bytesPerPixel) /*y*/};
  return ret;
}

float Image::calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness)
{
  return std::pow(inBrightness / maxInput, gamma) * maxOutput + 0.5;
}
