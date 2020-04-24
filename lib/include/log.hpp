#pragma once
#include <cstdint>

#include <fstream>
#include <mutex>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <pl/current_function.hpp>
#include <pl/string_view.hpp>

namespace l {
namespace detail {
class logger {
public:
  static logger& instance();

  template <class... Ts>
  void log(pl::string_view file, int64_t line, pl::string_view function,
           const Ts&... xs) {
    std::lock_guard<std::mutex> lock(mutex_);
    ofs_ << fmt::format("file: {}\nline: {}\nfunction: {}\n", file.data(), line,
                        function.line());
    ofs_ << "message: " << fmt::format(xs...) << '\n' << std::endl;
  }

private:
  explicit logger(pl::string_view log_file_path);

  std::ofstream ofs_;
  std::mutex mutex_;
};
} // namespace detail
} // namespace l

#define L_LOG(...)                                                             \
  ::l::detail::logger::instance().log(__FILE__, __LINE__, PL_CURRENT_FUNCTION, \
                                      __VA_ARGS__)
