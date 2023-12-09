#ifndef COMMANDDOA_H
#define COMMANDDOA_H

#include "commands.h"
#include "message.h"

namespace commands {
template<>
class Command<CommandId::DoA>
{
public:

  template<typename T, typename D, unsigned N>
  T getParam(const Message<D>&, common::ParseError &);

  template<typename D>
  bool matches(const Message<D>& m);

  template <typename D>
  Message<D> f(double d, int x)
  {
    Message<D> doc;
    return doc;
  }
};

template <>
double commands::Command<CommandId::DoA>::getParam<double, json::Doc, 0>(const Message<json::Doc> &message, common::ParseError &) {
  return 0.5f;
}

template<>
int commands::Command<CommandId::DoA>::getParam<int, json::Doc, 1>(const Message<json::Doc> &message, common::ParseError &)
{
  return 2;
}

template<>
bool commands::Command<CommandId::DoA>::matches<json::Doc>(const Message<json::Doc> &m)
{
  return false;
}

} // namespace commands
#endif // COMMANDDOA_H
