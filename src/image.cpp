#include "image.h"

#include <stdexcept>
#include <cmath>
#include <iostream>

class Image::Private
{
public:
  const Image::Format format;
  const unsigned int width{0};
  const unsigned int height{0};
  std::vector<uint8_t> data;

  Private(Image::Format format, unsigned int width, unsigned int height)
  : format{format}
  , width{width}
  , height{height}
  , data(Image::formatBpp(format) * width * height)
  {
  }
};

Image::Image(Format format, unsigned int width, unsigned int height)
: prv{std::make_unique<Private>(format, width, height)}
{
  if(! (prv->width && prv->height))
  {
    throw std::invalid_argument("Image < 1 pixel in at least one dinension");
  }
}

Image::Image(const Image& other)
{
  prv = std::make_unique<Private>(*other.prv);
}

Image::~Image() = default;

unsigned int Image::width() const
{
  return prv->width;
}

unsigned int Image::height() const
{
  return prv->height;
}

Image::Format Image::format() const
{
  return prv->format;
}

uint8_t* Image::data(unsigned int x, unsigned int y)
{
  if(x >= prv->width || y >= prv->height)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((y * prv->width + x) * formatBpp(prv->format));
}

const uint8_t* Image::data(unsigned int x, unsigned int y) const
{
  if(x >= prv->width || y >= prv->height)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((y * prv->width + x) * formatBpp(prv->format));
}

uint8_t* Image::data(Point<unsigned int> point)
{
  return data(point.x, point.y);
}

const uint8_t* Image::data(Point<unsigned int> point) const
{
  return data(point.x, point.y);
}

Image Image::toGrayscale() const
{
  switch(prv->format)
  {
    case Format::GRAY8:
    {
      return Image(*this);
    }
    case Format::RGB24:
    {
      Image ret(Format::GRAY8, prv->width, prv->height);
      const auto bytesPerPixel = formatBpp(prv->format);
      for(unsigned int i = 0; i < prv->width * prv->height; i++)
      {
        ret.prv->data[i] = static_cast<uint8_t>(
          prv->data[i * bytesPerPixel] * 0.299 // red
          + prv->data[i * bytesPerPixel + 1] * 0.587 // green
          + prv->data[i * bytesPerPixel + 2] * 0.114 // blue
        );
      }
      return ret;
    }
  }
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

Point<unsigned int> Image::indexToPosition(unsigned int index) const
{
  index /= formatBpp(prv->format);
  const auto bytesPerPixel = formatBpp(prv->format);
  Point<unsigned int> ret((index % prv->width) * bytesPerPixel /*x*/,
                          (index / prv->width) * bytesPerPixel /*y*/);
//std::cout << __func__ << "(): " << ret.x << "/" << ret.y
//          << std::endl;
  return ret;
}

float Image::calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness)
{
  return std::pow(inBrightness / maxInput, gamma) * maxOutput + 0.5;
}
