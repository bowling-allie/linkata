#ifndef LINKATA_SRC_LK_LOG_HPP_
#define LINKATA_SRC_LK_LOG_HPP_
#pragma once

#include <lk/lk.hpp>

#include <fmt/core.h>

#include <string>
#include <cstdio>

namespace lk::log {
  enum class level {
    VERBOSE = 2,
    DEBUG = 3,
    INFO = 4,
    WARN = 5,
    ERROR = 6,
    ASSERT = 7
  };

  void v(const std::string &tag, const std::string &message);
  void d(const std::string &tag, const std::string &message);
  void i(const std::string &tag, const std::string &message);
  void w(const std::string &tag, const std::string &message);
  void e(const std::string &tag, const std::string &message);
  void println(level log_level, const std::string &tag, const std::string &message);

  template <typename S, typename... Args>
  void v(const std::string &tag, const S &format_str, Args &&... args);

  template <typename S, typename... Args>
  void d(const std::string &tag, const S &format_str, Args &&... args);

  template <typename S, typename... Args>
  void i(const std::string &tag, const S &format_str, Args &&... args);

  template <typename S, typename... Args>
  void w(const std::string &tag, const S &format_str, Args &&... args);

  template <typename S, typename... Args>
  void e(const std::string &tag, const S &format_str, Args &&... args);

  template <typename S, typename... Args>
  void println(level log_level, const std::string &tag, const S &format_str, Args &&... args);

  namespace detail {
    char getLogLevelChar(level log_level);
    FILE *getLogFile(level log_level);
    std::string getCurrentDateTimeFormatted();
  }
}

#include "log.tpp"

#if defined(VA_OPT_SUPPORTED)
/// like lk::log::v(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_V(tag, format_str, ...) lk::log::v(tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
/// like lk::log::d(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_D(tag, format_str, ...) lk::log::d(tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
/// like lk::log::i(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_I(tag, format_str, ...) lk::log::i(tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
/// like lk::log::w(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_W(tag, format_str, ...) lk::log::w(tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
/// like lk::log::e(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_E(tag, format_str, ...) lk::log::e(tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
/// like lk::log::println(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_PRINTLN(log_level, tag, format_str, ...) lk::log::println(log_level, tag, FMT_STRING(format_str) __VA_OPT__(,) __VA_ARGS__)
#else
/// like lk::log::v(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_V(tag, format_str, ...) lk::log::v(tag, FMT_STRING(format_str),##__VA_ARGS__)
/// like lk::log::d(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_D(tag, format_str, ...) lk::log::d(tag, FMT_STRING(format_str),##__VA_ARGS__)
/// like lk::log::i(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_I(tag, format_str, ...) lk::log::i(tag, FMT_STRING(format_str),##__VA_ARGS__)
/// like lk::log::w(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_W(tag, format_str, ...) lk::log::w(tag, FMT_STRING(format_str),##__VA_ARGS__)
/// like lk::log::e(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_E(tag, format_str, ...) lk::log::e(tag, FMT_STRING(format_str),##__VA_ARGS__)
/// like lk::log::println(), but format_str is wrapped in FMT_STRING()
#define LK_LOG_PRINTLN(log_level, tag, format_str, ...) lk::log::println(log_level, tag, FMT_STRING(format_str),##__VA_ARGS__)
#endif

#endif //LINKATA_SRC_LK_LOG_HPP_
