#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <iostream>
#include <tuple>

using namespace std;

struct Json {};

struct Lora {};



enum CommandRef { SET_INFO_MEASURE };

namespace detail {

struct HostBase {
  using type = const char*;
  static constexpr bool isValid(type value) { return true; }
};

template <typename D> struct Host;

template <> struct Host<Json> : HostBase {
  static constexpr const typename HostBase::type id = "host";
};

template <typename D> struct Id;

template <> struct Id<Json> {
  using type = const char*;
  static constexpr const type id = "id";
};

template <CommandRef ref, typename D> struct MessageDetail;

template <typename Doc> struct MessageDetail<SET_INFO_MEASURE, Doc> {

  constexpr static const typename Id<Doc>::type id = "set_info_measure";

  /* Keep the order with the insertion order of the tuple
   to get the correct param fro*/
  enum Param { host, COUNT };

  static constexpr auto params = std::tuple<Host<Doc>>();

  template <Param num> static constexpr auto getParamInfo() {
    return std::get<num>(params);
  }
};

template <typename D> class DocDetail;

template <> class DocDetail<Json> {
public:
  template <typename ParamInfo>
  typename ParamInfo::type getParamValue(const Json& in, const ParamInfo& p) {
    return typename ParamInfo::type();
  };

  template <typename Param>
  bool paramIsValid(const Json& in, const Param& param) {
    return param.isValid(getParamValue(in, param));
  }

  template <typename... T, typename I, I... Is>
  bool constexpr messageIsValid(const Json& in, tuple<T...>,
                                integer_sequence<I, Is...>) {
    // checkParam(in, std::get<0>(params));
    //_run

           //    auto args = make_tuple(
           //        [&]() -> T
           //        {
           //          T v;
           //          if (!e.error)
           //          {
           //            v = cmd.template getParam<T, Is>(d, e);
           //          }
           //          return v;
           //        }()...);
    return false;
  }
};

} // namespace detail

template <typename D>
class ICommand {
  virtual D _run(const D& in) = 0;
};

template <CommandRef Ref, typename D> class Command : public ICommand<D> {

public:
  bool matches(const D& in) {
    return doc.getParamValue(in, detail::Id<D>()) == MessageSpec::id;
  }

  D run(const D& in) {
    /* Check message validity */
    doc.template messageIsValid(in, MessageSpec::params, paramsIndexSequence());
    return _run(in);
  }

protected:
  using MessageSpec = detail::MessageDetail<Ref, D>;
  detail::DocDetail<D> doc;

  virtual D _run(const D& in) = 0;

private:
  constexpr auto paramsIndexSequence() {
    return make_index_sequence<
        tuple_size<decltype(MessageSpec::params)>::value>();
  }
};

template <typename D>
class Command_SET_INFO_MEASURE : public Command<SET_INFO_MEASURE, D> {
public:
  constexpr Command_SET_INFO_MEASURE() : Command<SET_INFO_MEASURE, D>() {}
  virtual D _run(const D& in) {
    // doc.getParamValue(in, messageSpec.getParamInfo<MessageSpecType::host>());
    return Json();
  }
};
#endif // COMMAND_H
