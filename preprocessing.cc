#include "preprocessing.h"
#include "glog/logging.h"

namespace cortex {
absl::StatusOr<ImageFrame> LoadGrayscaleImage(absl::string_view image_path) {
  FILE* file_ptr = fopen(std::string(image_path).c_str(), "rb");
  if (file_ptr == nullptr) {
    return absl::InternalError(
        absl::StrFormat("Failed to open image file: %s", image_path));
  }

  BITMAPFILEHEADER bmp_header;
  BITMAPINFOHEADER bmp_info;

  if (fread(&bmp_header, sizeof(BITMAPFILEHEADER), 1, file_ptr) != 1 ||
      bmp_header.bfType != 0x4D42) {
    fclose(file_ptr);
    return absl::InvalidArgumentError("Not a valid BMP file");
  }

  if (fread(&bmp_info, sizeof(BITMAPINFOHEADER), 1, file_ptr) != 1 ||
      bmp_info.biBitCount != 8) {
    fclose(file_ptr);
    return absl::InvalidArgumentError("Not a grayscale BMP image");
  }
  // LOG(INFO) << "Debug:" << bmp_info.biWidth << " x " << bmp_info.biHeight << " bytes";

  int32_t width = bmp_info.biWidth;
  if (width & 0x03) {
    width = (width & ~0x03) + 4;
  }
  const int32_t height = bmp_info.biHeight;

  ImageFrame image_frame(width, height);
  fseek(file_ptr, bmp_header.bfOffBits, SEEK_SET);
  uint8_t* data_ptr = image_frame.MutablePixelData();

  for (int32_t row = height - 1; row >= 0; --row) {
    if (fread(data_ptr + row * width, sizeof(uint8_t), width, file_ptr) <
        static_cast<size_t>(width)) {
      fclose(file_ptr);
      return absl::DataLossError("Corrupted BMP image");
    }
  }

  return image_frame;
}
} // namespace cortext