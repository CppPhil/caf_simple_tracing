#include <cstdio>

#include <string>

#include <fmt/format.h>

#include "log.hpp"
#include "test_actor_buddy_function.hpp"
#include "test_profiler.hpp"
#include "test_tracing_data.hpp"

namespace l {
void test_actor_buddy_function(caf::event_based_actor* self,
                               const caf::actor& buddy) {
  using namespace std::string_literals;

  L_LOG("Spawned.");

  set_span_context("test_actor_buddy_function put this here.");
  L_LOG("About to send request");
  self->request(buddy, caf::infinite, "HiTheRe"s)
    .then([self](const std::string& result_string) {
      auto* trc_data = get_tracing_data(self);

      L_LOG("Received response.");

      if (trc_data == nullptr) {
        fmt::print(stderr,
                   "test_actor_buddy_function line {}: tracing_data was "
                   "nullptr, WTF?!?\n",
                   __LINE__);
        L_LOG("tracing_data was nullptr!");
      } else {
        fmt::print("test_actor_buddy_function line {}: tracing_data: \"{}\"\n",
                   __LINE__, trc_data->value);
        L_LOG("tracing_data was ok: \"{}\"", trc_data->value);
      }
    });
}
} // namespace l
