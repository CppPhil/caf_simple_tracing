#pragma once
#include <cstdio>

#include <fmt/format.h>

#include <caf/all.hpp>

namespace l {
class test_tracing_data : public caf::tracing_data {
public:
  std::string value;

  test_tracing_data(std::string value);

  caf::error serialize(caf::serializer& sink) const override;

  caf::error_code<caf::sec>
  serialize(caf::binary_serializer& sink) const override;
};

template <class T>
test_tracing_data* get_tracing_data(T& actor) {
  auto* mailbox_element = actor->current_mailbox_element();

  if (mailbox_element == nullptr) {
    fmt::print(stderr,
               "get_tracing_data: Couldn't get mailbox_element, WTF?????\n");
    return nullptr;
  }

  auto* tracing_id = mailbox_element->tracing_id.get();

  if (tracing_id == nullptr) {
    fmt::print(stderr, "get_tracing_data: Couldn't get tracing_id!!!\n");
    return nullptr;
  }

  auto* downcasted = dynamic_cast<test_tracing_data*>(tracing_id);

  if (downcasted == nullptr) {
    fmt::print(stderr, "get_tracing_data: Couldn't downcast, WTF????\n");
    return nullptr;
  }

  return downcasted;
}
} // namespace l
