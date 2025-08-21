#include "cortext_result.h"
#include "absl/strings/str_join.h"

namespace cortex {


bool CortexResult::operator==(const CortexResult& that) const {
  return data_length == that.data_length &&
         data == that.data &&
         symbol_type == that.symbol_type &&
         symbol_modifier == that.symbol_modifier &&
         decode_time == that.decode_time &&
         corners == that.corners &&
         center == that.center;
}

std::ostream& operator<<(std::ostream& os,
                         const CortexResult& result) {
  std::string corners_str = absl::StrCat(
      "[", absl::StrJoin(result.corners, ", "), "]");

  std::string center_str = absl::StrCat(
      "[", absl::StrJoin(result.center, ", "), "]");

  os << "CortexResult {"
      << "\n  data_length: " << result.data_length
      << "\n  data: \"" << result.data << "\""
      << "\n  symbol_type: " << result.symbol_type
      << "\n  symbol_modifier: " << result.symbol_modifier
      << "\n  decode_time: " << result.decode_time
      << "\n  corners: [";
  for (size_t i = 0; i < result.corners.size(); ++i) {
    os << result.corners[i] << (i == result.corners.size() - 1 ? "" : ", ");
  }
  os << "]"
      << "\n  center: [";
  for (size_t i = 0; i < result.center.size(); ++i) {
    os << result.center[i] << (i == result.center.size() - 1 ? "" : ", ");
  }
  os << "]\n}";
  return os;
}

} // namespace cortext