#ifndef COMMAND_CONTAINER_H
#define COMMAND_CONTAINER_H

#include "command.h"
#include <string>
#include <utility>
#include <tuple>



template <typename Cmd, typename... CtorArgs>
static constexpr Cmd make_command(CtorArgs &&...args) {
  return Cmd(std::forward<CtorArgs>(args)...);
};


template <typename... Ts>
class CommandContainer {
public:
  constexpr CommandContainer(const std::tuple<Ts...>& tuple) : _cmds(tuple) {}

  template <typename Doc>
  ICommand<Doc>* get(Doc& request) {
    ICommand<Doc>* cmd = nullptr;
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
  const std::tuple<Ts...>& _cmds;

};



#endif // COMMAND_CONTAINER_H
