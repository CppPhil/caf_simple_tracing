#include <caf/all.hpp>
#include <caf/io/all.hpp>

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
}

CAF_MAIN(caf::io::middleman)
