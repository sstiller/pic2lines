#include "jpeg.h"

#include <iostream>

#include <jpeglib.h>

#include <cstring>
#include <setjmp.h>

namespace
{

struct my_error_mgr
{
    struct jpeg_error_mgr pub;  // "public" fields
    jmp_buf setjmp_buffer;      // for return to caller
};

using my_error_ptr = struct my_error_mgr *;

void my_error_exit(j_common_ptr cinfo)
{
    // cinfo->err really points to a my_error_mgr struct, so coerce pointer
    auto myerr = (my_error_ptr) cinfo->err;

    // Always display the message.
    // We could postpone this until after returning, if we chose.
    (*cinfo->err->output_message) (cinfo);

    // Return control to the setjmp point
    longjmp(myerr->setjmp_buffer, 1);
}

} // anonymous namespace


std::shared_ptr<Image> readJpeg(const std::string& path)
{

//#error redo, perhaps use https://github.com/CelestiaProject/Celestia/blob/c74cd97422538479a508aae9a580357e3c73b277/src/celimage/jpeg.cpp#L130

  jpeg_decompress_struct cinfo;
  my_error_mgr jerr;

  JSAMPARRAY buffer{nullptr}; // output row
  int row_stride{0};    // physical row width in output buffer

  FILE* inFile = fopen(path.c_str(), "rb");

  if(! inFile)
  {
    throw std::system_error(errno, std::generic_category(), "Failed to open jpeg file " + path);
  }

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  // Establish the setjmp return context for my_error_exit to use.
  if (setjmp(jerr.setjmp_buffer))
  {
    // If we get here, the JPEG code has signaled an error.
    // We need to clean up the JPEG object, close the input file, and return.
    jpeg_destroy_decompress(&cinfo);
    fclose(inFile);

    throw std::runtime_error("Decode error");
  }

  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, inFile);
  jpeg_read_header(&cinfo, true);
  jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;
  buffer = (*cinfo.mem->alloc_sarray)
           ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  Image::Format format = Image::Format::RGB24;
  if (cinfo.output_components == 1)
      format = Image::Format::GRAY8;
  auto ret = std::make_shared<Image>(format, cinfo.image_width, cinfo.image_height);

  unsigned int lineNumber{0};
  while (cinfo.output_scanline < cinfo.output_height)
  {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    jpeg_read_scanlines(&cinfo, buffer, 1);

    memcpy(ret->data(0, lineNumber), buffer[0], row_stride);
    lineNumber++;
  }

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  fclose(inFile);

  return ret;
}
