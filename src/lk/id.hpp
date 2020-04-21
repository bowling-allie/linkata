#ifndef LINKATA_SRC_LK_ID_HPP_
#define LINKATA_SRC_LK_ID_HPP_
#pragma once

#include <lk/lk.hpp>

#include <Corrade/Containers/ArrayView.h>

#include <string>

namespace lk::id {
  std::string getCodepointArrayName(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array);

  namespace drawable {
    std::string emoji_png(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array);
    std::string emoji_svg(Corrade::Containers::ArrayView<const codepoint_type> codepoint_array);

    const static constexpr auto eye = "drawable/eye.png";
    const static constexpr auto eye_slash = "drawable/eye-slash.png";

    const static constexpr auto eye_svg = "drawable/eye.svg";
    const static constexpr auto eye_slash_svg = "drawable/eye-slash.svg";

    const static constexpr auto test_svg = "drawable/test.svg";
    const static constexpr auto tiger_svg = "drawable/Ghostscript_Tiger.svg";

    const static constexpr auto hello_kitty_svg = "drawable/hello_kitty.svg";
  }

  namespace fonts {
    const static constexpr auto roboto = "fonts/Roboto-Regular.ttf";
    //const static constexpr auto free_sans = "fonts/FreeSans.ttf";
    //const static constexpr auto fa_regular = "fonts/fa-regular-400.ttf";
  }
}

#endif //LINKATA_SRC_LK_ID_HPP_
