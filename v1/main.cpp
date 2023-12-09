#include "commandDoA.h"
#include <tuple>

using commands::make_command_runner;

int main() {

  std::tuple commands = make_tuple(make_command_runner<commands::CommandId::DoA>());


}


//  auto c = commands::make_command_runner<commands::CommandId::DoA>();
//  json::Doc doc;
//  common::ParseError e;
//  c.run(doc, e);

//  auto cmds = std::make_tuple(make_command_runner<commands::CommandId::DoA>());
//  auto c = std::get<static_cast<size_t>(commands::CommandId::DoA)>(cmds);


