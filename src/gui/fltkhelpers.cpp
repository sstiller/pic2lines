// local includes
#include "fltkhelpers.hpp"

// fltk
#include <FL/Fl_Image.H>

// std
#include <memory>
#include <string>

namespace FltkHelpers
{


Fl_Image* scaleWithAspectRatio(Fl_Image* originalImage,
                               uint16_t maxWidth,
                               int16_t maxHeight)
{
  if(!originalImage)
  {
    //displayErrorMessage(std::string(__PRETTY_FUNCTION__) + ": invalid input image");
    return nullptr;
  }

  const auto originalWidth{originalImage->w()};
  const auto originalHeight{originalImage->h()};
  if(! originalWidth && originalHeight)
  {
    //displayErrorMessage(std::string(__PRETTY_FUNCTION__) + ": invalid dimensions");
    return nullptr;
  }

  const auto scaleWidth = static_cast<double>(maxWidth) / originalWidth;
  const auto scaleHeight = static_cast<double>(maxHeight) / originalHeight;
  const auto scalingFactor = std::min(scaleWidth, scaleHeight);
  printf("Orig %dx%d\n", originalWidth, originalHeight);
  printf("copy %dx%d\n", static_cast<int>(originalWidth * scalingFactor), static_cast<int>(originalHeight * scalingFactor));

  return originalImage->copy(originalWidth * scalingFactor, originalHeight * scalingFactor);
}

class ResizableImageButton::Private
{
public:
  std::unique_ptr<Fl_Image> originalImage;
  std::unique_ptr<Fl_Image> scaledImage;
};

ResizableImageButton::ResizableImageButton(int X,
                                           int Y,
                                           int W,
                                           int H,
                                           const char* L)
: Fl_Button(X, Y, W, H, L)
, prv{std::make_unique<Private>()}
{
}

void ResizableImageButton::image(std::unique_ptr<Fl_Image> img)
{
  prv->originalImage = std::move(img); // Transfer ownership of the image
  scaleAndSetImage(prv->originalImage.get()); // Scale and display the image immediately
}

void ResizableImageButton::resize(int X, int Y, int W, int H)
{
  Fl_Button::resize(X, Y, W, H);
  scaleAndSetImage(prv->originalImage.get()); // Re-scale the image for the new size
}

void ResizableImageButton::scaleAndSetImage(Fl_Image* img)
{
  if (!img) return; // Guard against null images

  // Scale the image to fit the current dimensions of the button, maintaining aspect ratio
  Fl_Image* tempScaledImage = scaleWithAspectRatio(img, this->w() - 10, this->h() - 10);
  prv->scaledImage.reset(tempScaledImage); // Update the scaledImage pointer

  Fl_Button::image(prv->scaledImage.get()); // Set the scaled image for the button
  this->redraw(); // Redraw the button
}



} // namespace FltkHelpers

