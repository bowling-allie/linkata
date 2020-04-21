#ifndef LINKATA_SRC_LK_EMOJI_SVG_CACHE_HPP_
#define LINKATA_SRC_LK_EMOJI_SVG_CACHE_HPP_
#pragma once

#include <lk/lk.hpp>
#include <lk/emoji.hpp>
#include <lk/svg.hpp>

#include <unordered_map>

template<>
struct std::hash<lk::emoji::codepoint_array_type> {
  std::size_t operator()(const lk::emoji::codepoint_array_type &val) const noexcept;
};

template<>
struct std::hash<lk::emoji::codepoint_span_type> {
  std::size_t operator()(const lk::emoji::codepoint_span_type &val) const noexcept;
};

template<>
struct std::equal_to<lk::emoji::codepoint_array_type> {
  bool operator()(const lk::emoji::codepoint_array_type &x, const lk::emoji::codepoint_array_type &y) const noexcept;
};

template<>
struct std::equal_to<lk::emoji::codepoint_span_type> {
  bool operator()(const lk::emoji::codepoint_span_type &x, const lk::emoji::codepoint_span_type &y) const noexcept;
};

namespace lk {
  class emoji_svg_cache {
   public:
    emoji_svg_cache();

   private:
   public:
    std::unordered_map<emoji::codepoint_span_type, svg::handle> m_svgHandles{};
  };
}

#endif //LINKATA_SRC_LK_EMOJI_SVG_CACHE_HPP_
