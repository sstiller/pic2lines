#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "vec2.hpp"

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
  Image(Format format, const Dimensions<int>& dimensions);
  Image(const Image& other);
  ~Image();

  Dimensions<int> dimensions() const;
  Format format() const;

  uint8_t* data(const Point<int>& point = {0, 0});
  const uint8_t* data(const Point<int>& point = {0, 0}) const;

  std::shared_ptr<Image> toGrayscale() const;
  std::shared_ptr<Image> verticalFlip() const;

  /**
   * @brief formatBpp returns the bytes per pixels for the given format
   * @param format
   */
  static unsigned int formatBpp(Format format);
  static std::string formatToString(Format format);

  Point<int> indexToPosition(int index) const;

  static float calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness);

private:
  class Private;
  std::unique_ptr<Private> prv;

};

#endif // IMAGE_HPP
