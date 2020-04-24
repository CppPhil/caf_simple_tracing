#pragma once
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
} // namespace l
