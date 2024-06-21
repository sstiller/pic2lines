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

  [[nodiscard]] Dimensions<int> dimensions() const;
  [[nodiscard]] Format format() const;

  [[nodiscard]] uint8_t* data(const Point<int>& point = {0, 0});
  [[nodiscard]] const uint8_t* data(const Point<int>& point = {0, 0}) const;

  [[nodiscard]] std::shared_ptr<Image> toGrayscale() const;
  [[nodiscard]] std::shared_ptr<Image> verticalFlip() const;

  /**
   * @brief formatBpp returns the bytes per pixels for the given format
   * @param format
   */
  [[nodiscard]] static unsigned int formatBpp(Format format);
  [[nodiscard]] static std::string formatToString(Format format);

  [[nodiscard]] Point<int> indexToPosition(int index) const;

  [[nodiscard]] static float calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness);

private:
  class Private;
  std::unique_ptr<Private> prv;

};

#endif // IMAGE_HPP
