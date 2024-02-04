#include "App.h"
#include "command.h"
#include <iostream>
#include <tuple>





int main() {
  Command_SET_INFO_MEASURE<Json> cmd;
  Json j;
  auto matches = cmd.matches(j);
  cout << "Matches = " << matches << std::endl;

  cmd.run(j);

  App app;

  return 0;
}
