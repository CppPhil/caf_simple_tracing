#include <cstdio>

#include <caf/all.hpp>
#include <caf/io/all.hpp>

#include <fmt/format.h>

#include "log.hpp"
#include "test_actor_buddy_function.hpp"
#include "test_actor_function.hpp"
#include "test_profiler.hpp"
#include "test_tracing_data_factory.hpp"

namespace {
struct config : caf::actor_system_config {
  l::test_profiler test_profiler;
  l::test_tracing_data_factory test_tracing_context;

  config() {
    profiler = &test_profiler;
    tracing_context = &test_tracing_context;
  }
};
} // namespace

void caf_main(caf::actor_system& sys, const config& config) {
  const auto actor = sys.spawn(&l::test_actor_function);

  const auto expected_port = caf::io::publish(actor, 1337, "0.0.0.0");

  if (expected_port) {
    fmt::print("node_b successfully published\n");
  } else {
    fmt::print(stderr, "node_b couldn't publish\n");
  }
}

CAF_MAIN(caf::io::middleman)
