#include "image.h"

#include <stdexcept>

class Image::Private
{
public:
  const Image::Format format;
  const unsigned int width{0};
  const unsigned int height{0};
  std::vector<char> data;

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
}

Image::~Image()
{
}

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

char* Image::data(unsigned int x, unsigned int y)
{
  if(x >= prv->width || y >= prv->height)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((y * prv->width + x) * formatBpp(prv->format));
}

const char* Image::data(unsigned int x, unsigned int y) const
{
  if(x >= prv->width || y >= prv->height)
  {
    throw std::out_of_range("data pos > image dimensions");
  }
  return &prv->data.at((y * prv->width + x) * formatBpp(prv->format));
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
