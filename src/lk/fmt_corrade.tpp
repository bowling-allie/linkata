#include <fmt/format.h>

/// Corrade::Containers::Array<T>
#if 1
#include <Corrade/Containers/Array.h>

template<typename T>
struct fmt::formatter<Corrade::Containers::Array<T>> {
 private:
  using type = Corrade::Containers::Array<T>;
  using element_type = decltype(*std::declval<type>().begin());
  static constexpr bool isMultiDimensional = Corrade::Utility::IsIterable<element_type>::value && !Corrade::Utility::IsStringLike<element_type>::value;
  static constexpr const char *separator = (isMultiDimensional ? ",\n " : ", ");

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "{{");
    const auto begin = std::begin(value);
    for (auto it = begin; it != std::end(value); ++it) {
      if (it != begin) fmt::format_to(ctx.out(), separator);
      fmt::format_to(ctx.out(), "{}", *it);
    }
    return fmt::format_to(ctx.out(), "}}");
  }
};
#endif

/// Corrade::Containers::ArrayView<T>
/// Corrade::Containers::StaticArrayView<Size, T>
#if 1
#include <Corrade/Containers/ArrayView.h>

template<typename T>
struct fmt::formatter<Corrade::Containers::ArrayView<T>> {
 private:
  using type = Corrade::Containers::ArrayView<T>;
  using element_type = decltype(*std::declval<type>().begin());
  static constexpr bool isMultiDimensional = Corrade::Utility::IsIterable<element_type>::value && !Corrade::Utility::IsStringLike<element_type>::value;
  static constexpr const char *separator = (isMultiDimensional ? ",\n " : ", ");

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "{{");
    const auto begin = std::begin(value);
    for (auto it = begin; it != std::end(value); ++it) {
      if (it != begin) fmt::format_to(ctx.out(), separator);
      fmt::format_to(ctx.out(), "{}", *it);
    }
    return fmt::format_to(ctx.out(), "}}");
  }
};

template<std::size_t Size, typename T>
struct fmt::formatter<Corrade::Containers::StaticArrayView<Size, T>> {
 private:
  using type = Corrade::Containers::StaticArrayView<Size, T>;
  using element_type = decltype(*std::declval<type>().begin());
  static constexpr bool isMultiDimensional = Corrade::Utility::IsIterable<element_type>::value && !Corrade::Utility::IsStringLike<element_type>::value;
  static constexpr const char *separator = (isMultiDimensional ? ",\n " : ", ");

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "{{");
    const auto begin = std::begin(value);
    for (auto it = begin; it != std::end(value); ++it) {
      if (it != begin) fmt::format_to(ctx.out(), separator);
      fmt::format_to(ctx.out(), "{}", *it);
    }
    return fmt::format_to(ctx.out(), "}}");
  }
};
#endif

/// Corrade::Containers::EnumSet<T, fullValue>
#if 1
#include <Corrade/Containers/EnumSet.hpp>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<typename T, typename std::underlying_type<T>::type fullValue>
struct fmt::formatter<Corrade::Containers::EnumSet<T, fullValue>> {
 private:
  using type = Corrade::Containers::EnumSet<T, fullValue>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Corrade::Containers::NullOptT
/// Corrade::Containers::Optional<T>
#if 1
#include <Corrade/Containers/Optional.h>

template<>
struct fmt::formatter<Corrade::Containers::NullOptT> {
 private:
  using type = Corrade::Containers::NullOptT;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Containers::NullOpt");
  }
};

template<typename T>
struct fmt::formatter<Corrade::Containers::Optional<T>> {
 private:
  using type = Corrade::Containers::Optional<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    if(!value) {
      fmt::format_to(ctx.out(), "{}", Corrade::Containers::NullOpt);
    } else {
      fmt::format_to(ctx.out(), "{}", *value);
    }
    return ctx.out();
  }
};
#endif

/// Corrade::Containers::Pointer<T>
#if 1
#include <Corrade/Containers/Pointer.h>

template<typename T>
struct fmt::formatter<Corrade::Containers::Pointer<T>> {
 private:
  using type = Corrade::Containers::Pointer<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "{}", value.get());
  }
};
#endif

/// Corrade::Containers::Reference<T>
#if 1
#include <Corrade/Containers/Reference.h>

template<typename T>
struct fmt::formatter<Corrade::Containers::Reference<T>> {
 private:
  using type = Corrade::Containers::Reference<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "{}", value.get());
  }
};
#endif

/// Corrade::Containers::StaticArray<Size, T>
#if 1
#include <Corrade/Containers/StaticArray.h>

template<std::size_t Size, typename T>
struct fmt::formatter<Corrade::Containers::StaticArray<Size, T>> {
 private:
  using type = Corrade::Containers::StaticArray<Size, T>;
  using element_type = decltype(*std::declval<type>().begin());
  static constexpr bool isMultiDimensional = Corrade::Utility::IsIterable<element_type>::value && !Corrade::Utility::IsStringLike<element_type>::value;
  static constexpr const char *separator = (isMultiDimensional ? ",\n " : ", ");

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "{{");
    const auto begin = std::begin(value);
    for (auto it = begin; it != std::end(value); ++it) {
      if (it != begin) fmt::format_to(ctx.out(), separator);
      fmt::format_to(ctx.out(), "{}", *it);
    }
    return fmt::format_to(ctx.out(), "}}");
  }
};
#endif

/// Corrade::Containers::StridedArrayView<Size, T>
#if 1
#include <Corrade/Utility/Debug.h>

template<unsigned Dimensions, typename T>
struct fmt::formatter<Corrade::Containers::StridedArrayView<Dimensions, T>> {
 private:
  using type = Corrade::Containers::StridedArrayView<Dimensions, T>;
  using element_type = decltype(*std::declval<type>().begin());
  static constexpr bool isMultiDimensional = Corrade::Utility::IsIterable<element_type>::value && !Corrade::Utility::IsStringLike<element_type>::value;
  static constexpr const char *separator = (isMultiDimensional ? ",\n " : ", ");

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "{{");
    const auto begin = std::begin(value);
    for (auto it = begin; it != std::end(value); ++it) {
      if (it != begin) fmt::format_to(ctx.out(), separator);
      fmt::format_to(ctx.out(), "{}", *it);
    }
    return fmt::format_to(ctx.out(), "}}");
  }
};
#endif

/// Corrade::PluginManager::LoadState
#if 1
#include <Corrade/PluginManager/AbstractManager.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Corrade::PluginManager::LoadState> {
 private:
  using type = Corrade::PluginManager::LoadState;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Corrade::TestSuite::ComparisonStatusFlag
#if 1
#include <Corrade/TestSuite/Comparator.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Corrade::TestSuite::ComparisonStatusFlag> {
 private:
  using type = Corrade::TestSuite::ComparisonStatusFlag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Corrade::Utility::HashDigest<Size>
#if 1
#include <Corrade/Utility/AbstractHash.h>

template<std::size_t Size>
struct fmt::formatter<Corrade::Utility::HashDigest<Size>> {
 private:
  using type = Corrade::Utility::HashDigest<Size>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "{}", value.hexString());
  }
};
#endif

/// Corrade::Utility::Debug::Flag
/// Corrade::Utility::Debug::Color
#if 1
#include <Corrade/Utility/AbstractHash.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Corrade::Utility::Debug::Flag> {
 private:
  using type = Corrade::Utility::Debug::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Corrade::Utility::Debug::Color> {
 private:
  using type = Corrade::Utility::Debug::Color;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Corrade::Utility::FileWatcher::Flag
#if 1
#include <Corrade/Utility/FileWatcher.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Corrade::Utility::FileWatcher::Flag> {
 private:
  using type = Corrade::Utility::FileWatcher::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif
