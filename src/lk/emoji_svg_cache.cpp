#include "emoji_svg_cache.hpp"

#include <lk/emoji.hpp>
#include <lk/id.hpp>
#include <lk/util.hpp>
#include <lk/resource.hpp>

#include <Corrade/Utility/System.h>
#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
#include <Corrade/Utility/DebugStl.h>

#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Range.h>

#include <fmt/core.h>

#include <boost/container_hash/hash.hpp>

/*
namespace {
  struct Vertex {
    Magnum::Vector2 position;
    Magnum::Vector2 textureCoordinates;
  };
}
*/

std::size_t std::hash<lk::emoji::codepoint_array_type>::operator()(const lk::emoji::codepoint_array_type &val) const noexcept {
  return boost::hash_range(val.cbegin(), val.cend());
}

std::size_t std::hash<lk::emoji::codepoint_span_type>::operator()(const lk::emoji::codepoint_span_type &val) const noexcept {
  return boost::hash_range(val.cbegin(), val.cend());
}

bool std::equal_to<lk::emoji::codepoint_array_type>::operator()(const lk::emoji::codepoint_array_type &x, const lk::emoji::codepoint_array_type &y) const noexcept {
  return (x.size() == y.size()) && std::equal(x.cbegin(), x.cend(), y.cbegin());
}

bool std::equal_to<lk::emoji::codepoint_span_type>::operator()(const lk::emoji::codepoint_span_type &x, const lk::emoji::codepoint_span_type &y) const noexcept {
  return (x.size() == y.size()) && std::equal(x.cbegin(), x.cend(), y.cbegin());
}

lk::emoji_svg_cache::emoji_svg_cache() {
  for (auto &codepoints_list_ : emoji::codepoints_list) {
    //if (codepoints_list_.size() > 1) continue;
    Corrade::Containers::ArrayView<const codepoint_type> codepoints_{std::data(codepoints_list_), codepoints_list_.size()};
    //std::copy(codepoints_list_.begin(), codepoints_list_.end(), codepoints_array_.begin());
    std::vector<char> svg_vector{};
    {
      auto svg_resource = resource{id::drawable::emoji_svg(codepoints_), true, false};
      auto svg_data = svg_resource.getData();
      svg_vector.resize(svg_data.size() + 1);
      std::copy(svg_data.cbegin(), svg_data.cend(), svg_vector.begin());
    }
    auto handle = svg::parse(svg_vector.data());
    auto tmp = m_svgHandles.emplace(
        codepoints_,
        std::move(handle)
    );
  }
}
