#include <cstdio>

#include <fmt/format.h>

#include "log.hpp"
#include "test_profiler.hpp"
#include "test_tracing_data.hpp"

namespace l {
namespace {
thread_local std::string span_context;
} // namespace

void set_span_context(const std::string& span_ctx) {
  span_context = span_ctx;
}

void set_span_context(std::string&& span_ctx) {
  span_context = std::move(span_ctx);
}

void set_span_context(const char* span_ctx) {
  span_context = span_ctx;
}

test_profiler::test_profiler() = default;

void test_profiler::add_actor(const caf::local_actor&,
                              const caf::local_actor*) {
}

void test_profiler::remove_actor(const caf::local_actor&) {
}

void test_profiler::before_processing(const caf::local_actor& actor,
                                      const caf::mailbox_element& element) {
  const auto& trace_id = element.tracing_id;

  if (trace_id == nullptr) {
    fmt::print(stderr, "before_processing: tracing_id was NULLPTR!\n");
    L_LOG("tracing_id was null!");
  } else {
    fmt::print("before_processing: tracing_id was ok!\n");
    L_LOG("tracing_id isn't null");
  }
}

void test_profiler::after_processing(const caf::local_actor&,
                                     caf::invoke_message_result) {
}

void test_profiler::before_sending(const caf::local_actor& actor,
                                   caf::mailbox_element& element) {
  if (element.tracing_id == nullptr) {
    element.tracing_id = std::make_unique<test_tracing_data>(span_context);
    fmt::print("before_sending: set tracing_id to \"{}\"\n", span_context);
    L_LOG("tracing_id set to \"{}\"", span_context);
  } else {
    fmt::print(stderr, "before_sending: tracing_id wasn't null, WHAT?!?");
    L_LOG("Unexpected: tracing_id wasn't null.");
  }
}

void test_profiler::before_sending_scheduled(
  const caf::local_actor& self, caf::actor_clock::time_point timeout,
  caf::mailbox_element& element) {
  if (element.tracing_id == nullptr) {
    element.tracing_id = std::make_unique<test_tracing_data>(span_context);
    fmt::print("before_sending_scheduled: set tracing_id to \"{}\"\n",
               span_context);
    L_LOG("tracing_id set to \"{}\"", span_context);
  } else {
    fmt::print(stderr,
               "before_sending_scheduled: tracing_id wasn't null, WHAT?!?");
    L_LOG("Unexpected: tracing_id wasn't null.");
  }
}
} // namespace l
