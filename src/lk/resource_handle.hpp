#ifndef LINKATA_SRC_LK_RESOURCE_HANDLE_HPP_
#define LINKATA_SRC_LK_RESOURCE_HANDLE_HPP_
#pragma once

#include <lk/lk.hpp>

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Containers/Pointer.h>

#if defined(LINKATA_EMBED_RESOURCES)
#define LINKATA_RESOURCE_HANDLE_TYPE Corrade::Containers::ArrayView<const char>
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
#include <emscripten/fetch.h>
#define LINKATA_RESOURCE_HANDLE_TYPE emscripten_fetch_t
#else
#include <Corrade/Containers/Array.h>
#define LINKATA_RESOURCE_HANDLE_TYPE Corrade::Containers::Array<char>
#endif
#endif

namespace lk {
  class resource_handle {
   public:
    using handle_type = LINKATA_RESOURCE_HANDLE_TYPE;
    using data_type = Corrade::Containers::ArrayView<const char>;
    using release_data_type = Corrade::Containers::Array<char>;

    static const constexpr bool can_release_data =
#if defined(LINKATA_EMBED_RESOURCES)
        false
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
        false
#else
        true
#endif
#endif
    ;

    /// delete copy constructors
    resource_handle(const resource_handle &) = delete;
    resource_handle &operator=(const resource_handle &) = delete;

    resource_handle(resource_handle &&other_) noexcept = default;
    resource_handle &operator=(resource_handle &&other_) noexcept = default;

    explicit resource_handle(Corrade::Containers::Pointer<handle_type> init_handle_);
    ~resource_handle();

    [[nodiscard]] Corrade::Containers::Pointer<handle_type> release();

    [[nodiscard]] data_type getData() const;
    [[nodiscard]] release_data_type releaseData();

   private:
    Corrade::Containers::Pointer<handle_type> m_handle;
  };
}

#endif //LINKATA_SRC_LK_RESOURCE_HANDLE_HPP_
