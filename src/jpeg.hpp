#ifndef JPEG_HPP
#define JPEG_HPP

#include "image.hpp"

#include <string>
#include <memory>

[[nodiscard]] std::shared_ptr<Image> readJpeg(const std::string& path);

#endif // JPEG_HPP
