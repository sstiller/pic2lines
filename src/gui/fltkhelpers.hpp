#ifndef FLTKHELPERS_HPP
#define FLTKHELPERS_HPP

// fltk
#include <FL/Fl.H>
#include <Fl/Fl_Button.H>

// std
#include <algorithm>
#include <memory>
// C
#include <cstdint>

namespace FltkHelpers
{

Fl_Image* scaleWithAspectRatio(Fl_Image* originalImage,
                               uint16_t maxWidth,
                               int16_t maxHeight);

class ResizableImageButton : public Fl_Button
{
public:
  ResizableImageButton(int X, int Y, int W, int H, const char* L = nullptr);
  void image(std::unique_ptr<Fl_Image> img);

protected:
  void resize(int X, int Y, int W, int H) override;

private:
  class Private;
  std::unique_ptr<Private> prv;

  void scaleAndSetImage(Fl_Image* img);

};

} // namespace FltkHelpers


#endif // FLTKHELPERS_HPP
