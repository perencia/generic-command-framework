#ifndef APP_H
#define APP_H

#include "command.h"
#include "command_container.h"

using CmdType = Json;


class App {
public:
  static constexpr const auto cmds = make_tuple(Command_SET_INFO_MEASURE<CmdType>());
  /* Move the code to get a command from the container to the processor
   * and do not use the container.*/
  static constexpr const auto cmdContainer = CommandContainer(cmds);

private:



};

#endif // APP_H
