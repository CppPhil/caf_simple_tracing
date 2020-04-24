#include <cstdio>

#include <algorithm>

#include <fmt/format.h>

#include "log.hpp"
#include "test_actor_function.hpp"
#include "test_profiler.hpp"
#include "test_tracing_data.hpp"

namespace l {
caf::behavior test_actor_function(caf::event_based_actor* self) {
  L_LOG("Spawned.");

  return {
    [self](std::string s) {
      L_LOG("Received string: \"{}\"", s);
      auto* trac_data = get_tracing_data(self);

      if (trac_data == nullptr) {
        fmt::print(stderr,
                   "test_actor_function: tracing_data was null, WTF?\n");
        L_LOG("tracing_data was null!");
      } else {
        fmt::print("test_actor_function: tracing_data: \"{}\"\n",
                   trac_data->value);
        L_LOG("tracing_data is ok: \"{}\"", trac_data->value);
      }

      std::transform(s.begin(), s.end(), s.begin(), [](char c) {
        return static_cast<char>(static_cast<unsigned char>(c) & ~0x20U);
      });

      L_LOG("After transformation: \"{}\"", s);

      L_LOG("About to set span_context");
      set_span_context("test_actor_function put this here");

      L_LOG("About to respond.");
      return s;
    },
  };
}
} // namespace l
