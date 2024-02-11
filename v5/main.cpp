#include "tuple.hpp"
#include <iostream>

using namespace std;

class EEPROM {};

namespace param {

namespace source {
class EEPROM;
class JSon;
} // namespace source

template <typename T> class ParamEEPROM {

private:
  const T& mInstance;

public:
  ParamEEPROM(const T& instance) : mInstance(instance) {}
  template <typename EEPROM>
  T read(const EEPROM& storage, uint32_t addr) const {
    // Check is valid, etc..
    return T{};
  }
  template <typename EEPROM>
  bool store(const EEPROM& storage, uint32_t addr, const T& val) {
    return false;
  }
};

class A : public ParamEEPROM<int> {
public:
  A() : ParamEEPROM<int>(*this) {}
};

class B : public ParamEEPROM<bool> {
public:
  B() : ParamEEPROM<bool>(*this) {}
};

namespace detail {}

template <typename Params, typename... Ts> class ParamsDelegate {

private:
  const Params& mParams;
  kumi::tuple<Ts...> t{};

public:
  ParamsDelegate(const Params& params) : mParams(params) {}

  template <typename Source> bool from(const Source&);

  /* Cannot do a from<source::eeprom> ->
   * https://stackoverflow.com/questions/3052579/explicit-specialization-in-non-namespace-scope
   */
  bool fromEEPROM() {
    kumi::for_each(
        [&](const auto& p) {
          // Read and treat errors.
          p.read(mParams.storage(), mParams.template address<decltype(p)>());
        },
        t);
    return false;
  }

  template <typename Sink> bool to(const Sink&);
  bool toEEPROM();

  template <typename T> auto get(){};
  template <typename T> auto set(){};
};

template <typename Storage> class Params {

private:
  const Storage& mStorage;

public:
  Params(const Storage& storage) : mStorage(storage) {}
  template <typename... Ts> auto get() {
    return ParamsDelegate<Params<Storage>, Ts...>(*this);
  }

  template <typename T> uint32_t address() const { return 0; }

  const Storage& storage() const { return mStorage; }
};
} // namespace param

using namespace param;

int main() {
  EEPROM eeprom;
  Params p(eeprom);

  auto _ps = p.get<A>();
  //_ps.read();
}
