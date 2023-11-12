#include "jpeg.h"

#include <iostream>

#include <jpeglib.h>

#include <cstring>
#include <setjmp.h>

namespace
{

struct ErrorMgr
{
    struct jpeg_error_mgr pub;  // "public" fields
    jmp_buf setjmpBuffer;      // for return to caller
};


void my_error_exit(j_common_ptr cinfo)
{
    // cinfo->err really points to a my_error_mgr struct, so coerce pointer
    auto myerr = (ErrorMgr*) cinfo->err;

    // Always display the message.
    // We could postpone this until after returning, if we chose.
    (*cinfo->err->output_message) (cinfo);

    // Return control to the setjmp point
    longjmp(myerr->setjmpBuffer, 1);
}

} // anonymous namespace


std::shared_ptr<Image> readJpeg(const std::string& path)
{

//#error redo, perhaps use https://github.com/CelestiaProject/Celestia/blob/c74cd97422538479a508aae9a580357e3c73b277/src/celimage/jpeg.cpp#L130

  jpeg_decompress_struct decompressInfo;
  ErrorMgr errMgr;

  JSAMPARRAY outputRow{nullptr}; // output row
  int rowStride{0};    // physical row width in outputRow

  FILE* inFile = fopen(path.c_str(), "rb");

  if(! inFile)
  {
    throw std::system_error(errno, std::generic_category(), "Failed to open jpeg file " + path);
  }

  decompressInfo.err = jpeg_std_error(&errMgr.pub);
  errMgr.pub.error_exit = my_error_exit;
  // Establish the setjmp return context for my_error_exit to use.
  if(setjmp(errMgr.setjmpBuffer))
  {
    // If we get here, the JPEG code has signaled an error.
    // We need to clean up the JPEG object, close the input file, and return.
    jpeg_destroy_decompress(&decompressInfo);
    fclose(inFile);

    throw std::runtime_error("Decode error");
  }

  jpeg_create_decompress(&decompressInfo);
  jpeg_stdio_src(&decompressInfo, inFile);
  jpeg_read_header(&decompressInfo, true);
  jpeg_start_decompress(&decompressInfo);

  rowStride = decompressInfo.output_width * decompressInfo.output_components;
  outputRow = (*decompressInfo.mem->alloc_sarray)
           ((j_common_ptr) &decompressInfo, JPOOL_IMAGE, rowStride, 1);

  Image::Format format = Image::Format::RGB24;
  if (decompressInfo.output_components == 1)
      format = Image::Format::GRAY8;
  auto ret = std::make_shared<Image>(format, Dimensions<int>{static_cast<int>(decompressInfo.image_width),
                                                             static_cast<int>(decompressInfo.image_height)});

  int lineNumber{0};
  while (decompressInfo.output_scanline < decompressInfo.output_height)
  {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    jpeg_read_scanlines(&decompressInfo, outputRow, 1);

    memcpy(ret->data({0, lineNumber}), outputRow[0], rowStride);
    lineNumber++;
  }

  jpeg_finish_decompress(&decompressInfo);
  jpeg_destroy_decompress(&decompressInfo);

  fclose(inFile);

  return ret;
}
