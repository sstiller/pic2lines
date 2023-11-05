#ifndef IMAGE_H
#define IMAGE_H

#include "point.h"

#include <memory>
#include <vector>

class Image
{
public:
  enum class Format
  {
    RGB24,
    GRAY8
  };
  Image(Format format, unsigned int width, unsigned int height);
  Image(const Image& other);
  ~Image();

  unsigned int width() const;
  unsigned int height() const;
  Format format() const;

  uint8_t* data(unsigned int x = 0, unsigned int y = 0);
  const uint8_t* data(unsigned int x = 0, unsigned int y = 0) const;
  uint8_t* data(Point<unsigned int> point);
  const uint8_t* data(Point<unsigned int> point) const;


  Image toGrayscale() const;

  /**
   * @brief formatBpp returns the bytes per pixes for the given format
   * @param format
   */
  static unsigned int formatBpp(Format format);
  static std::string formatToString(Format format);

  Point<unsigned int> indexToPosition(unsigned int index) const;

  static float calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness);

private:
  class Private;
  std::unique_ptr<Private> prv;

};

#endif // IMAGE_H
