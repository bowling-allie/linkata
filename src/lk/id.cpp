#include "id.hpp"

#include <fmt/core.h>

std::string lk::id::getCodepointArrayName(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array) {
  if (codepoint_array.empty()) return "";
  std::string filename{};
  filename.reserve(codepoint_array.size() * 6);
  filename.append(fmt::format("{:x}", codepoint_array[0]));

  for (int i = 1; i < codepoint_array.size(); ++i) {
    filename.append(fmt::format("-{:x}", codepoint_array[i]));
  }
  filename.shrink_to_fit();
  return std::move(filename);
}

std::string lk::id::drawable::emoji_png(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array) {
  return fmt::format("drawable/emojis/72x72/{:s}.png", getCodepointArrayName(codepoint_array));
}

std::string lk::id::drawable::emoji_svg(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array) {
  return fmt::format("drawable/emojis/svg/{:s}.svg", getCodepointArrayName(codepoint_array));
}
