#include "resource_handle.hpp"

lk::resource_handle::resource_handle(Corrade::Containers::Pointer<handle_type> init_handle_)
    : m_handle{std::move(init_handle_)} {}

lk::resource_handle::~resource_handle() {
#if defined(LINKATA_EMBED_RESOURCES)
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
  // todo: finish
  emscripten_fetch_close(m_handle.release());
#error
#else
#endif
#endif
}

Corrade::Containers::Pointer<lk::resource_handle::handle_type> lk::resource_handle::release() {
  return std::move(m_handle);
}

lk::resource_handle::data_type lk::resource_handle::getData() const {
  if (!m_handle) Corrade::Utility::Fatal{} << "lk::resource_handle::getData() - handle is null!";

#if defined(LINKATA_EMBED_RESOURCES)
  return {*m_handle};
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
#error
#else
  return {*m_handle};
#endif
#endif
}

lk::resource_handle::release_data_type lk::resource_handle::releaseData() {
  if constexpr (!lk::resource_handle::can_release_data) {
    Corrade::Utility::Error{} << "lk::resource_handle::releaseData() - can_release_data is false!";
#if defined(LINKATA_EMBED_RESOURCES)
    Corrade::Utility::Fatal{} << "lk::resource_handle::releaseData() - Cannot release embedded resources";
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
    // todo: finish
#error
#else
    Corrade::Utility::Fatal{} << "lk::resource_handle::releaseData() - unreachable";
#endif
#endif
  } else {
    if (!m_handle) Corrade::Utility::Fatal{} << "lk::resource_handle::releaseData() - handle is null!";
#if defined(LINKATA_EMBED_RESOURCES)
    Corrade::Utility::Fatal{} << "lk::resource_handle::releaseData() - unreachable";
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
    Corrade::Utility::Fatal{} << "lk::resource_handle::releaseData() - unreachable";
#else
    return std::move(*m_handle);
#endif
#endif
  }
}
