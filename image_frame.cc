#include "image_frame.h"

namespace cortex {
ImageFrame::ImageFrame(ImageFrame&& move_from) { *this = std::move(move_from); }

ImageFrame& ImageFrame::operator=(ImageFrame&& move_from) {
  pixel_data_ = std::move(move_from.pixel_data_);
  width_ = move_from.width_;
  height_ = move_from.height_;

  move_from.width_ = 0;
  move_from.height_ = 0;
  return *this;
}

ImageFrame::ImageFrame() : width_(0), height_(0) {
}

ImageFrame::ImageFrame(int32_t width, int32_t height) : width_(width),
  height_(height) {
  pixel_data_ = std::make_unique<uint8_t[]>(width * height);
}
} // namespace cortex
