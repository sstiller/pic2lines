#ifndef JPEG_H
#define JPEG_H

#include "image.hpp"

#include <string>
#include <memory>

std::shared_ptr<Image> readJpeg(const std::string& path);

#endif // JPEG_H
