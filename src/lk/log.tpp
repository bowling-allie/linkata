#include <fmt/core.h>
//#include <fmt/ostream.h>

#include <lk/fmt_corrade.tpp>
#include <lk/fmt_magnum.tpp>

template<typename S, typename... Args>
void lk::log::v(const std::string &tag, const S &format_str, Args &&... args) {
  println(level::VERBOSE, tag, format_str, args...);
}

template<typename S, typename... Args>
void lk::log::d(const std::string &tag, const S &format_str, Args &&... args) {
  println(level::DEBUG, tag, format_str, args...);
}

template<typename S, typename... Args>
void lk::log::i(const std::string &tag, const S &format_str, Args &&... args) {
  println(level::INFO, tag, format_str, args...);
}

template<typename S, typename... Args>
void lk::log::w(const std::string &tag, const S &format_str, Args &&... args) {
  println(level::WARN, tag, format_str, args...);
}

template<typename S, typename... Args>
void lk::log::e(const std::string &tag, const S &format_str, Args &&... args) {
  println(level::ERROR, tag, format_str, args...);
}

template<typename S, typename... Args>
void lk::log::println(level log_level, const std::string &tag, const S &format_str, Args &&... args) {
  println(log_level, tag, fmt::format(format_str, args...));
}
