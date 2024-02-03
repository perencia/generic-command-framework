#ifndef STORAGEEEPROM_H
#define STORAGEEEPROM_H

#endif // STORAGEEEPROM_H

#include "tuple.hpp"
#include <functional>
#include <iostream>
#include <string>

class Host {
public:
  using type = int;
};

class SampleOn {
public:
  using type = bool;
};

namespace kumi {

template <size_t I, typename... Ts>
constexpr auto tuple_element(const tuple<Ts...>& t)
    -> std::remove_cvref_t<decltype(kumi::get<I>(t))> {}
} // namespace kumi

const kumi::tuple<Host, SampleOn> items;

template <typename T> class EEPROMAddr {
public:
  template <typename U>
  static constexpr unsigned _addr(std::index_sequence<>, U) {
    return 0;
  }

  template <typename U, U... Is, typename... Ts>
  static constexpr unsigned _addr(std::index_sequence<Is...>,
                                  const kumi::tuple<Ts...> t) {
    return ((sizeof(typename decltype(kumi::tuple_element<Is>(t))::type)) +
            ...);
  }

  template <typename... Ts>
  static constexpr unsigned addr(const kumi::tuple<Ts...> t) {
    constexpr auto index = kumi::locate(
        t, [](auto e) constexpr { return std::is_same_v<decltype(e), T>; });
    return _addr(std::make_index_sequence<index>(), t);
  }
};

int main() {
  constexpr auto a = (EEPROMAddr<SampleOn>::addr(items));
  static_assert(a == 4);
  std::cout << a << std::endl;
}
