#ifndef LINKATA_SRC_LK_CORRADE_DEBUG_STREAM_UTIL_HPP_
#define LINKATA_SRC_LK_CORRADE_DEBUG_STREAM_UTIL_HPP_
#pragma once

#include <Corrade/Utility/DebugStl.h>
#include <type_traits>

namespace detail {

  template<typename T>
  typename std::add_lvalue_reference<T>::type declare_lvalue_reference() noexcept;

  CORRADE_HAS_TYPE(
      has_debug_stream_operator,
      typename std::enable_if<std::is_same<
          decltype(declare_lvalue_reference<Corrade::Utility::Debug>() << std::declval<T>()),
          std::add_lvalue_reference<Corrade::Utility::Debug>::type
      >::value>::type
  );

  CORRADE_HAS_TYPE(
      has_ostream_operator,
      typename std::enable_if<std::is_same<
          decltype(declare_lvalue_reference<std::ostream>() << std::declval<T>()),
          std::add_lvalue_reference<std::ostream>::type
      >::value>::type
  );
/*
  template<typename T>
  struct has_ostream_operator {
   private:
    template<typename C>
    static constexpr auto check(C *) ->
    typename std::is_same<
        decltype(declare_lvalue_reference<std::ostream>() << std::declval<C>()),
        std::add_lvalue_reference<std::ostream>::type
    >::type;

    template<typename>
    static constexpr std::false_type check(...);

   public:
    static constexpr bool value = decltype(check<T>(nullptr))::value;
  };
*/
}

template<typename T>
typename std::enable_if<
    detail::has_debug_stream_operator<T>::value
        && detail::has_debug_stream_operator<T>::value,
    std::ostream
>::type &operator<<(std::ostream &os, const T &val) {
  static thread_local Corrade::Utility::Debug debug{&os, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
  debug << val;
  return os;
}

#endif //LINKATA_SRC_LK_CORRADE_DEBUG_STREAM_UTIL_HPP_
