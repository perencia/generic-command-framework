#ifndef COMMAND2_H
#define COMMAND2_H

#include "command.h"
#include <iostream>

namespace waveco {

template <typename Doc> class Command2 : public Command<Doc> {

public:
  Command2(detail::Id<Doc>::type id) : Command<Doc>(id) {}
  virtual Doc run(const Doc &doc) const {}
};

template <> JsonDoc Command2<JsonDoc>::run(const JsonDoc &doc) const {
  JsonDoc d;
  d["id"] = _id;
  return d;
}
template <> LoraDoc Command2<LoraDoc>::run(const LoraDoc &doc) const {
  LoraDoc d;
  d.id = '2';
  std::cout << "Command 2 run" << std::endl;
  return d;
}
} // namespace waveco

#endif // COMMAND2_H
