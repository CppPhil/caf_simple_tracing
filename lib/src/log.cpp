#include "log.hpp"

namespace l {
namespace detail {
logger& logger::instance() {
  static logger log_instance("simple_caf_tracing.log");
  return log_instance;
}

logger::logger(pl::string_view log_file_path)
  : ofs_(log_file_path.data(), std::ios_base::out | std::ios_base::trunc),
    mutex_() {
  // nop
}
} // namespace detail
} // namespace l
