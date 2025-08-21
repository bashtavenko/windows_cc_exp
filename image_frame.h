#ifndef IMAGE_FRAME_H
#define IMAGE_FRAME_H

#include <memory>

namespace cortex {
// A container for storing an image or a video frame.
// https://github.com/google-ai-edge/mediapipe/blob/master/mediapipe/framework/formats/image_frame.h
class ImageFrame {
public:
  // Not copyable or constructible
  ImageFrame(const ImageFrame&) = delete;
  ImageFrame& operator=(const ImageFrame&) = delete;
  ImageFrame(ImageFrame&& move_from);
  ImageFrame& operator=(ImageFrame&& move_from);

  // Creates an empty ImageFrame. It will need to be initialized by some other
  // means.
  ImageFrame();

  // Allocates a frame of the appropriates size.  Does not zero it out.
  ImageFrame(int32_t width, int32_t height);

  // Returns true if the ImageFrame is unallocated.
  bool IsEmpty() const { return pixel_data_ == nullptr; }

  // Returns the width of the image in pixels.
  int32_t Width() const { return width_; }
  // Returns the height of the image in pixels.
  int32_t Height() const { return height_; }

  // Get a mutable pointer to the underlying image data.  The ImageFrame
  // retains ownership.
  uint8_t* MutablePixelData() { return pixel_data_.get(); }

  // Get a const uint8_t pointer to the underlying image data.
  const uint8_t* PixelData() const { return pixel_data_.get(); }

  // Get a void pointer to the underlying image data.
  void* VoidPixelData() const { return pixel_data_.get(); }

private:
  std::unique_ptr<uint8_t[]> pixel_data_;
  int32_t width_;
  int32_t height_;
};
}


#endif //IMAGE_FRAME_H
