#include "command_container.h"
#include "command2.h"
#include "command3.h"
#include "processor.h"
#include <iostream>
#include <tuple>

using namespace std;

using CmdType = LoraDoc;

int main() {

  auto cmds = make_tuple(waveco::make_command<waveco::Command2<CmdType>>('2'),
                         waveco::make_command<waveco::Command3<CmdType>>('3',3));

  auto commandContainer = waveco::CommandContainer(cmds);
  const char* msg = "3";
  waveco::Processor<CmdType, decltype(commandContainer)> processor(commandContainer);
  auto response = processor.process(msg);
  std::cout << response.id;
  return 0;
}



       //  Command<CmdType> cmd('0');
       //  auto cmd = cmds[0];
       //  const std::array<Command<CmdType>, 1> cmds = {cmd};
       //  const char* msg = R"cmd({"id":"echo"})cmd";
