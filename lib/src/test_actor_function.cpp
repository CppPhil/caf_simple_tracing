#include <cstdio>

#include <algorithm>

#include <fmt/format.h>

#include "test_actor_function.hpp"
#include "test_profiler.hpp"
#include "test_tracing_data.hpp"

namespace l {
caf::behavior test_actor_function(caf::event_based_actor* self) {
  return {
    [self](std::string s) {
      auto* trac_data = get_tracing_data(self);

      if (trac_data == nullptr) {
        fmt::print(stderr,
                   "test_actor_function: tracing_data was null, WTF?\n");
      } else {
        fmt::print("test_actor_function: tracing_data: \"{}\"\n",
                   trac_data->value);
      }
      std::transform(s.begin(), s.end(), s.begin(), [](char c) {
        return static_cast<char>(static_cast<unsigned char>(c) & ~0x20U);
      });

      set_span_context("test_actor_function put this here");
      return s;
    },
  };
}
} // namespace l
