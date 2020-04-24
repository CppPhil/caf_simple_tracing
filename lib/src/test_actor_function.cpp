#include <algorithm>

#include "test_actor_function.hpp"
#include "test_profiler.hpp"

namespace l {
caf::behavior test_actor_function(caf::event_based_actor* self) {
  return {
    [self](std::string s) {
      std::transform(s.begin(), s.end(), s.begin(), [](char c) {
        return static_cast<char>(static_cast<unsigned char>(c) & ~0x20U);
      });

      set_span_context("test_actor_function put this here");
      return s;
    },
  };
}
} // namespace l
