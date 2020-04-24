#include "test_tracing_data.hpp"

namespace l {
test_tracing_data::test_tracing_data(std::string value)
  : value(std::move(value)) {
}

caf::error test_tracing_data::serialize(caf::serializer& sink) const {
  return sink(value);
}

caf::error_code<caf::sec>
test_tracing_data::serialize(caf::binary_serializer& sink) const {
  return sink(value);
}
} // namespace l
