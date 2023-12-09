#ifndef COMMAND3_H
#define COMMAND3_H

#include "command.h"
#include <iostream>

namespace waveco {

template <typename Doc> class Command3 : public Command<Doc> {
private:
  int _num;
public:
  Command3(detail::Id<Doc>::type id, int num) : Command<Doc>(id), _num(num) {}
  virtual Doc run(const Doc &doc) const {}
};

template <> JsonDoc Command3<JsonDoc>::run(const JsonDoc &doc) const {
  JsonDoc d;
  d["id"] = _id;
  return d;
}
template <> LoraDoc Command3<LoraDoc>::run(const LoraDoc &doc) const {
  LoraDoc d;
  itoa(_num, &d.id, 10);
  std::cout << "Command 3 run" << std::endl;
  return d;
}
} // namespace waveco

#endif // COMMAND3_H
