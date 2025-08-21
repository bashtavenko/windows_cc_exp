#ifndef CORTEX_DECODER_H
#define CORTEX_DECODER_H

#include "absl/status/status.h"
#include <windows.h>
#include <functional>
#include <mutex>
#include <unordered_map>
#include "image_frame.h"


#include "absl/status/statusor.h"
#include "absl/synchronization/mutex.h"
#include "absl/synchronization/notification.h"
#include "cortext_result.h"


namespace cortex {
class CortexDecoder {
public:
  ~CortexDecoder();

  absl::Status Init();

  bool IsReady() const;

  int32_t Handle() const { return handle_; }

  // Decodes "single" with callback
  absl::Status DecodeSingle(const ImageFrame& image_frame,
                            std::function<void(const CortexResult&)> on_result);

  // Decodes multiple and blocks
  absl::StatusOr<std::vector<CortexResult> > DecodeMultiple(
      const ImageFrame& image_frame);

  absl::StatusOr<CortexResult> OnResult(int32_t handle);

private:
  int32_t handle_ = -1;
  absl::Mutex mutex_;

  // Static members used for C -> C++ routing
  static std::unordered_map<int32_t, CortexDecoder*> s_instance_registry_
  ABSL_GUARDED_BY(mutex_);
  static absl::Mutex s_registry_mutex_;

  // Static helper functions for registration/unregistration
  static void RegisterInstance(int handle, CortexDecoder* instance);

  static void UnregisterInstance(int32_t handle);

  // CortextDecoder calls this.
  static int StaticOnResultThunk(int handle);

  // Forwading between C++ std::function and c callback.
  std::function<void(const CortexResult&)> on_result_callback_;

  static constexpr size_t kMaxImageSize = 4 * 1024 * 1024;
};
} // namespace cortex

#endif //CORTEX_DECODER_H


