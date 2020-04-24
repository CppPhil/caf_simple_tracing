#include <cstdio>

#include <string>

#include <fmt/format.h>

#include "test_actor_buddy_function.hpp"
#include "test_tracing_data.hpp"

namespace l {
void test_actor_buddy_function(caf::event_based_actor* self,
                               const caf::actor& buddy) {
  using namespace std::string_literals;

  auto* trac_data = get_tracing_data(self);

  if (trac_data == nullptr) {
    fmt::print(
      stderr,
      "test_actor_buddy_function line {}: tracing_data was nullptr, WTF?????\n",
      __LINE__);
  } else {
    fmt::print("test_actor_buddy_function line {}: tracing_data: \"{}\"\n",
               __LINE__, trac_data->value);
  }

  self->request(buddy, caf::infinite, "HiTheRe"s)
    .then([self](const std::string& result_string) {
      auto* trc_data = get_tracing_data(self);

      if (trc_data == nullptr) {
        fmt::print(stderr,
                   "test_actor_buddy_function line {}: tracing_data was "
                   "nullptr, WTF?!?\n",
                   __LINE__);
      } else {
        fmt::print("test_actor_buddy_function line {}: tracing_data: \"{}\"\n",
                   __LINE__, trc_data->value);
      }
    });
}
} // namespace l
