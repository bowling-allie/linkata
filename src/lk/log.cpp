#include "log.hpp"

//#include <boost/iostreams/stream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <fmt/core.h>
//#include <fmt/color.h>

#include <string>

namespace {
  //auto null_ostream{boost::iostreams::stream<boost::iostreams::null_sink>((boost::iostreams::null_sink()))};
}

void lk::log::v(const std::string &tag, const std::string &message) {
  println(level::VERBOSE, tag, message);
}

void lk::log::d(const std::string &tag, const std::string &message) {
  println(level::DEBUG, tag, message);
}

void lk::log::i(const std::string &tag, const std::string &message) {
  println(level::INFO, tag, message);
}

void lk::log::w(const std::string &tag, const std::string &message) {
  println(level::WARN, tag, message);
}

void lk::log::e(const std::string &tag, const std::string &message) {
  println(level::ERROR, tag, message);
}

void lk::log::println(level log_level, const std::string &tag, const std::string &message) {
  FILE *file_ = detail::getLogFile(log_level);
  fmt::print(
      file_,
      "{} {}/{}: {}\n",
      detail::getCurrentDateTimeFormatted(),
      detail::getLogLevelChar(log_level),
      tag,
      message
  );
  std::fflush(file_);
}

char lk::log::detail::getLogLevelChar(lk::log::level log_level) {
  switch (log_level) {
    case lk::log::level::VERBOSE:
      return 'V';
    case lk::log::level::DEBUG:
      return 'D';
    case lk::log::level::INFO:
      return 'I';
    case lk::log::level::WARN:
      return 'W';
    case lk::log::level::ERROR:
      return 'E';
    case lk::log::level::ASSERT:
      return 'A';
    default:
      return '?';
  }
}

FILE *lk::log::detail::getLogFile(lk::log::level log_level) {
  switch (log_level) {
    case lk::log::level::VERBOSE:
    case lk::log::level::DEBUG:
    case lk::log::level::INFO:
      return stdout;
    case lk::log::level::WARN:
    case lk::log::level::ERROR:
    case lk::log::level::ASSERT:
      return stderr;
    default:
      return nullptr;
  }
}

std::string lk::log::detail::getCurrentDateTimeFormatted() {
  boost::posix_time::ptime timeLocal = boost::posix_time::microsec_clock::local_time();
  std::ostringstream date_time_stream{};
  date_time_stream << timeLocal;
  return date_time_stream.str();
}
