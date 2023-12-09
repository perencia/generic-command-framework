#ifndef COMMAND_CONTAINER_H
#define COMMAND_CONTAINER_H

#include "command.h"

#include <utility>
#include <tuple>

namespace waveco {
template <typename Cmd, typename... CtorArgs>
static Cmd make_command(CtorArgs &&...args) {
  return Cmd(std::forward<CtorArgs>(args)...);
};


template <typename... Ts>
class CommandContainer {
public:
  constexpr CommandContainer(std::tuple<Ts...>& tuple) : _cmds(tuple) {}

  template <typename Doc> Command<Doc>* get(Doc& request) {
    Command<Doc>* cmd = nullptr;
    invoke(std::make_index_sequence<sizeof...(Ts)>{}, [&]<typename Command>(Command& c){
      return c.matches(request) ? (cmd = &c, true) : false;
    });
    return cmd;
  }
private:
  template <typename TPred, size_t... Is>
  bool invoke(std::index_sequence<Is...>, TPred pred) {
    return (((pred(std::get<Is>(_cmds)))) || ...);
  }
  std::tuple<Ts...>& _cmds;

};
} //namespace waveco



#endif // COMMAND_CONTAINER_H
