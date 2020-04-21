#ifndef LINKATA_SRC_LK_EMOJI_HPP_
#define LINKATA_SRC_LK_EMOJI_HPP_
#pragma once

#include <lk/lk.hpp>

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/ArrayView.h>

namespace lk::emoji {
  using codepoint_array_type = Corrade::Containers::Array<codepoint_type>;
  using codepoint_span_type = Corrade::Containers::ArrayView<const codepoint_type>;

  extern const std::initializer_list<const unsigned int> codepoints_list[3107];
}

#endif //LINKATA_SRC_LK_EMOJI_HPP_
