#ifndef LINKATA_SRC_LK_RESOURCE_HPP_
#define LINKATA_SRC_LK_RESOURCE_HPP_
#pragma once

#include <lk/lk.hpp>

#include <lk/resource_handle.hpp>

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/ArrayView.h>

#if defined(LINKATA_EMBED_RESOURCES)
#define LINKATA_ASYNC_RESOURCE_HANDLE_TYPE Corrade::Containers::ArrayView<const char>
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
#include <emscripten/fetch.h>
#define LINKATA_ASYNC_RESOURCE_HANDLE_TYPE emscripten_fetch_t
#else
//#include <Corrade/Utility/Directory.h>
#include <Corrade/Containers/Array.h>
#define LINKATA_ASYNC_RESOURCE_HANDLE_TYPE Corrade::Containers::Array<char>
#endif
#endif

#include <future>
#include <mutex>
#include <string>

namespace lk {
  /**
   * generated destructor will call ~std::future<void>(), which will wait for data to be ready.
   *
   * you may experience "hangs" when lk::resource goes out of scope and data is not ready yet
   */
  class resource {
   public:
    static const constexpr bool is_synchronous =
#if defined(LINKATA_EMBED_RESOURCES)
        true
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
    false
#else
    false
#endif
#endif
    ;

    /// delete copy constructors
    resource(const resource &) = delete;
    resource &operator=(const resource &) = delete;

    resource(resource &&other_) noexcept = default;
    resource &operator=(resource &&other_) noexcept = default;

    explicit resource(std::string init_id_, bool fetch_ = true, bool async_ = true);

    [[nodiscard]] const std::string &getId() const;

    /**
     * if true, getData() can be called
     * @return
     */
    [[nodiscard]] bool isReady() const;

    void fetch(bool async_ = true);

    /**
     * @return a non-owning ArrayView object pointing to the data
     */
    [[nodiscard]] resource_handle::data_type getData() const;

    /**
     * errors if lk::resource_handle::can_release_data is false
     * releases the handle This object is invalid after this is called
     * @return an Array object owning the data
     */
    resource_handle::release_data_type releaseData();

   private:
    std::string m_id;
    std::future<void> m_ready{};
    std::shared_ptr<std::mutex> m_sharedResourceHandleMutex{nullptr};
    std::shared_ptr<std::unique_ptr<resource_handle>> m_sharedResourceHandlePtr{nullptr};
  };
}

#endif //LINKATA_SRC_LK_RESOURCE_HPP_
