#ifndef IMAGE_H
#define IMAGE_H

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
  ~Image();

  unsigned int width() const;
  unsigned int height() const;
  Format format() const;

  char* data(unsigned int x = 0, unsigned int y = 0);
  const char* data(unsigned int x = 0, unsigned int y = 0) const;

  /**
   * @brief formatBpp returns the bytes per pixes for the given format
   * @param format
   */
  static unsigned int formatBpp(Format format);
  static std::string formatToString(Format format);

  static float calculateBrightness(float gamma, float maxInput, float maxOutput, float inBrightness);

private:
  class Private;
  std::unique_ptr<Private> prv;

};

#endif // IMAGE_H
