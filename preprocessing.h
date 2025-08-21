#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <windows.h>
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "image_frame.h"

namespace cortex {

absl::StatusOr<ImageFrame> LoadGrayscaleImage(absl::string_view image_path);

}


#endif //PREPROCESSING_H
