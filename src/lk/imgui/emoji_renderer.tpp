#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/ArrayView.h>
#include <boost/container_hash/hash.hpp>

template<typename T>
struct std::hash<Corrade::Containers::Array<T>> {
  std::size_t operator()(const Corrade::Containers::Array<T> &val) const noexcept {
    return boost::hash_range(val.cbegin(), val.cend());
  }
};

template<typename T>
struct std::hash<Corrade::Containers::ArrayView<T>> {
  std::size_t operator()(const Corrade::Containers::ArrayView<T> &val) const noexcept {
    return boost::hash_range(val.cbegin(), val.cend());
  }
};

template<typename T>
struct std::equal_to<Corrade::Containers::Array<T>> {
  bool operator()(const Corrade::Containers::Array<T> &x, const Corrade::Containers::Array<T> &y) const noexcept {
    return (x.size() == y.size()) && std::equal(x.cbegin(), x.cend(), y.cbegin());
  }
};

template<typename T>
struct std::equal_to<Corrade::Containers::ArrayView<T>> {
  bool operator()(const Corrade::Containers::ArrayView<T> &x, const Corrade::Containers::ArrayView<T> &y) const noexcept {
    return (x.size() == y.size()) && std::equal(x.cbegin(), x.cend(), y.cbegin());
  }
};