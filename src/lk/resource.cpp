#include "resource.hpp"
#include "util.hpp"

#include <Corrade/Utility/Debug.h>

#if defined(LINKATA_EMBED_RESOURCES)
#include <Corrade/Utility/Resource.h>
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
#else
#include <Corrade/Utility/Directory.h>
#endif
#endif

namespace {
#if defined(LINKATA_EMBED_RESOURCES)
  auto &getResourceGroup() {
    static Corrade::Utility::Resource resource_group_{"res"};
    return resource_group_;
  }
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
  /*
  using get_promise_type;
  using get_future_type;
  void get_onsuccess(emscripten_fetch_t *fetch_) {
    Corrade::Utility::Debug{} << "Finished downloading " << fetch_->numBytes << " bytes from URL '" << fetch_->url << "'";
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    ///auto promise_ = reinterpret_cast<get_promise_type *>(fetch_->userData);
    // todo: FIX, fetch handle gets lost so emscripten_fetch_close() cant be called to free data
    promise_->set_value(Corrade::Containers::ArrayView<const char>{fetch_->data, static_cast<std::size_t>(fetch_->numBytes)});
    //emscripten_fetch_close(fetch_); // Free data associated with the fetch.
  }

  void get_onerror(emscripten_fetch_t *fetch_) {
    Corrade::Utility::Fatal{} << "Downloading '" << fetch_->url << "' failed, HTTP failure status code: " << fetch_->status;
    emscripten_fetch_close(fetch_); // Also free data on failure.
  }
*/

  using persist_promise_type = std::promise<void>;
  using persist_future_type = std::future<void>;

  void persist_onsuccess(emscripten_fetch_t *fetch_) {
    Corrade::Utility::Debug{} << "Finished downloading and persisting " << fetch_->numBytes << " bytes from URL '" << fetch_->url << "'";
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    auto promise_ = reinterpret_cast<persist_promise_type *>(fetch_->userData);
    promise_->set_value();
    delete promise_;
    emscripten_fetch_close(fetch_); // Free data associated with the fetch.
  }

  void persist_onerror(emscripten_fetch_t *fetch_) {
    Corrade::Utility::Fatal{} << "Downloading and persisting '" << fetch_->url << "' failed, HTTP failure status code: " << fetch_->status;
    auto promise_ = reinterpret_cast<persist_promise_type *>(fetch_->userData);
    promise_->set_value();
    delete promise_;
    emscripten_fetch_close(fetch_); // Also free data on failure.
  }
#else
#endif
#endif
}

lk::resource::resource(std::string init_id_, bool fetch_, bool async_) : m_id{std::move(init_id_)} {
  if (fetch_) fetch(async_);
}

const std::string &lk::resource::getId() const {
  return m_id;
}

bool lk::resource::isReady() const {
  return m_ready.wait_for(std::chrono::system_clock::duration::zero()) == std::future_status::ready;
}

void lk::resource::fetch(bool async_) {
  if (!m_sharedResourceHandlePtr) {
    m_sharedResourceHandlePtr.reset(new std::unique_ptr<resource_handle>{});
  } else {
    if ((*m_sharedResourceHandlePtr))
      Corrade::Utility::Fatal{} << "lk::resource::fetch() - (*m_sharedResourceHandlePtr) is non-null!";
  }
  if (!m_sharedResourceHandleMutex) m_sharedResourceHandleMutex = std::make_shared<std::mutex>();

#if defined(LINKATA_EMBED_RESOURCES)
  std::lock_guard<std::mutex> lock_{*m_sharedResourceHandleMutex};
  m_sharedResourceHandlePtr->reset(new resource_handle{Corrade::Containers::Pointer{
      new Corrade::Containers::ArrayView<const char>{
          getResourceGroup().getRaw(m_id)
      }
  }});
  std::promise<void> temp_promise_{};
  m_ready = temp_promise_.get_future();
  temp_promise_.set_value();
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
  persist_promise_type *promise_ = new persist_promise_type{};

  emscripten_fetch_attr_t fetch_attr_;
  emscripten_fetch_attr_init(&fetch_attr_);
  std::strncpy(fetch_attr_.requestMethod, "EM_IDB_STORE", 32);
  fetch_attr_.userData = &promise_;
  fetch_attr_.attributes = EMSCRIPTEN_FETCH_PERSIST_FILE;
  fetch_attr_.onsuccess = persist_onsuccess;
  fetch_attr_.onerror = persist_onerror;
  emscripten_fetch(&fetch_attr_, id_.c_str());

  return {[ready_ = promise_->get_future()]() -> bool {
    return ready_.wait_for(std::chrono::system_clock::duration::zero()) == std::future_status::ready;
  }};
#else
  if (async_) {
    m_ready = std::async(std::launch::async, [
        id_{m_id},
        shared_resource_handle_mutex_{m_sharedResourceHandleMutex},
        shared_resource_handle_ptr_{m_sharedResourceHandlePtr}
    ]() -> void {
      namespace Directory = Corrade::Utility::Directory;
      auto data_ptr_ = new resource_handle{Corrade::Containers::Pointer{
          new Corrade::Containers::Array<char>{
              Directory::read(Directory::join({Directory::current(), util::getResDir(), id_}))
          }
      }};
      if (!shared_resource_handle_mutex_)
        Corrade::Utility::Fatal{} << "lk::resource::fetch()::lambda - shared_resource_handle_mutex_ is null!";
      if (!shared_resource_handle_ptr_)
        Corrade::Utility::Fatal{} << "lk::resource::fetch()::lambda - shared_resource_handle_ptr_ is null!";
      if ((*shared_resource_handle_ptr_))
        Corrade::Utility::Fatal{} << "lk::resource::fetch()::lambda - (*shared_resource_handle_ptr_) is non-null!";
      // todo: possible(not probable) race hazard if ptrs get nulled here somehow
      std::lock_guard<std::mutex> lock_{*shared_resource_handle_mutex_};
      shared_resource_handle_ptr_->reset(data_ptr_);
    });
  } else {
    namespace Directory = Corrade::Utility::Directory;
    auto data_ptr_ = new resource_handle{Corrade::Containers::Pointer{
        new Corrade::Containers::Array<char>{
            Directory::read(Directory::join({Directory::current(), util::getResDir(), m_id}))
        }
    }};

    std::lock_guard<std::mutex> lock_{*m_sharedResourceHandleMutex};
    m_sharedResourceHandlePtr->reset(data_ptr_);

    std::promise<void> temp_promise_{};
    m_ready = temp_promise_.get_future();
    temp_promise_.set_value();
  }
#endif
#endif
}

lk::resource_handle::data_type lk::resource::getData() const {
  if (!isReady())
    Corrade::Utility::Fatal{} << "lk::resource::getData() - not ready!";
  if (!m_sharedResourceHandleMutex)
    Corrade::Utility::Fatal{} << "lk::resource::getData() - m_sharedResourceHandleMutex is null!";
  if (!m_sharedResourceHandlePtr)
    Corrade::Utility::Fatal{} << "lk::resource::getData() - m_sharedResourceHandlePtr is null!";
  if (!(*m_sharedResourceHandlePtr))
    Corrade::Utility::Fatal{} << "lk::resource::getData() - (*m_sharedResourceHandlePtr) is null!";

  std::lock_guard<std::mutex> lock_{*m_sharedResourceHandleMutex};
  return (*m_sharedResourceHandlePtr)->getData();
}

lk::resource_handle::release_data_type lk::resource::releaseData() {
  if (!isReady())
    Corrade::Utility::Fatal{} << "lk::resource::releaseData() - not ready!";
  if (!m_sharedResourceHandleMutex)
    Corrade::Utility::Fatal{} << "lk::resource::releaseData() - m_sharedResourceHandleMutex is null!";
  if (!m_sharedResourceHandlePtr)
    Corrade::Utility::Fatal{} << "lk::resource::releaseData() - m_sharedResourceHandlePtr is null!";
  if (!(*m_sharedResourceHandlePtr))
    Corrade::Utility::Fatal{} << "lk::resource::releaseData() - (*m_sharedResourceHandlePtr) is null!";

  std::lock_guard<std::mutex> lock_{*m_sharedResourceHandleMutex};
  return (*m_sharedResourceHandlePtr)->releaseData();
}
