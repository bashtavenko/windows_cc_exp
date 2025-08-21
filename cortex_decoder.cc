#include "cortex_decoder.h"
#include <absl/strings/str_cat.h>
#include "glog/logging.h"
#include <unordered_map>
#include <mutex>
#include "image_frame.h"
#include "absl/strings/str_join.h"

namespace cortex {
// Definition of the static, C-compatible callback thunk.
// THIS is where 'extern "C"' belongs.
extern "C" int32_t CortexDecoder::StaticOnResultThunk(int32_t handle) {
  absl::MutexLock lock(&s_registry_mutex_);
  auto it = s_instance_registry_.find(handle);
  if (it == s_instance_registry_.end()) return -1;
  CortexDecoder* instance = it->second;
  CHECK(instance);

  auto status = instance->OnResult(handle);
  if (!status.ok()) return -1;
  // Invoking client callback
  instance->on_result_callback_(status.value());
  return 0;
}

// This is a member function that was called from C
absl::StatusOr<CortexResult> CortexDecoder::OnResult(
    int32_t handle) {

  int32_t data_length = 0;
  char data[1024] = {};
  int32_t bound[8] = {};
  int32_t center[2] = {};
  int32_t symbol_type = 0;
  int32_t symbol_modifier = 0;

  // Some business logic

  data[data_length] = '\0';

  CortexResult result;
  result.data = std::string(data, data_length);
  result.corners.assign(bound, bound + 8);
  result.center.assign(center, center + 2);
  result.symbol_type = symbol_type;
  result.symbol_modifier = symbol_modifier;
  return result;
}


// Static member definitions
void CortexDecoder::RegisterInstance(int handle, CortexDecoder* instance) {
  absl::MutexLock lock(&s_registry_mutex_);
  s_instance_registry_[handle] = instance;
}

void CortexDecoder::UnregisterInstance(int32_t handle) {
  absl::MutexLock lock(&s_registry_mutex_);
  s_instance_registry_.erase(handle);
}

std::unordered_map<int32_t, CortexDecoder*> CortexDecoder::s_instance_registry_;
absl::Mutex CortexDecoder::s_registry_mutex_;

CortexDecoder::~CortexDecoder() {
  if (IsReady()) {
    UnregisterInstance(handle_);
    // Destroy other
  }
};

absl::Status CortexDecoder::Init() {
  // Some logic
  RegisterInstance(handle_, this); {
    absl::MutexLock lock(&s_registry_mutex_);
    s_instance_registry_[handle_] = this;
  }
  return absl::OkStatus();
}

bool CortexDecoder::IsReady() const {
  return handle_ >= 0 && handle_ < 999;
}

absl::Status CortexDecoder::DecodeSingle(const ImageFrame& image_frame,
                                         std::function<void
                                           (const CortexResult&)> on_result) {
  on_result_callback_ = on_result;
  // Some logic
  const int32_t decode_result = 1; // CRD_Decode(handle_);
  if (decode_result != 0) {
    return absl::InternalError(
        absl::StrCat("Decoding failed: ", decode_result));
  }
  return absl::OkStatus();
}

} // namespace cortext
