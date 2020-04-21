#ifndef LINKATA_SRC_LK_SVG_HPP_
#define LINKATA_SRC_LK_SVG_HPP_

#include <lk/lk.hpp>

#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/Pointer.h>

#include <Magnum/Magnum.h>
#include <Magnum/Math/Range.h>

#include <nanosvg.h>

#include <nanovg.h>

#include <string>

namespace lk::svg {
  struct handle {
    using type = NSVGimage;

    /// delete copy constructors
    handle(const handle &) = delete;
    handle &operator=(const handle &) = delete;

    handle(handle &&other_) noexcept = default;
    handle &operator=(handle &&other_) noexcept = default;

    handle(type *init_ = nullptr) noexcept;

    ~handle();

    Corrade::Containers::Pointer<type> m_handle;
  };

  namespace detail {
    NVGcontext *getNvgContext();
  }

  /**
   * Important note: changes the string.
   * @param svg_data a mutable c-string (does not take ownership)
   */
  handle parse(char *svg_data);
  void draw(handle &svg_handle, Corrade::Containers::Optional<Magnum::Range2D> size = {});
}

#endif //LINKATA_SRC_LK_SVG_HPP_
