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
  L_LOG("About to spawn test_actor_function");
  auto test_actor = sys.spawn(&l::test_actor_function);
  L_LOG("Spawned test_actor_function");

  L_LOG("About to spawn test_actor_buddy_function");
  sys.spawn(&l::test_actor_buddy_function, test_actor);
  L_LOG("Spawned test_actor_buddy_function");
}

CAF_MAIN(caf::io::middleman)
