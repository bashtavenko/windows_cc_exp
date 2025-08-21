#ifndef CODE_CORP_EXP_CORTEXT_RESULT_H
#define CODE_CORP_EXP_CORTEXT_RESULT_H

#include <cstdint>
#include <string>
#include <vector>

namespace cortex {
// Result of barcode decoding
struct CortexResult {
  CortexResult() : data_length(0), symbol_type(0), symbol_modifier(0),
                   decode_time(0) {
  }

  int32_t data_length;
  std::string data;
  int32_t symbol_type;
  int32_t symbol_modifier;
  // Barcode decode time from the beginning of CRD_DecodeMultiEx
  int32_t decode_time;
  // Each corner has two integers for x and y coordinates.
  // There are 8 corners.
  std::vector<int32_t> corners;
  // The center point has two integers for x and y coordinates
  std::vector<int32_t> center;

  bool operator==(const CortexResult& that) const;

  friend std::ostream& operator<<(std::ostream& os,
                                  const CortexResult& result);
};
}


#endif //CODE_CORP_EXP_CORTEXT_RESULT_H