#ifndef COMMANDDOA_H
#define COMMANDDOA_H

#include "commands.h"

namespace commands {
template<>
class Command<CommandId::DoA>
{
public:
    template<typename T, unsigned N>
    T getParam(const json::Doc &, common::ParseError &);


    bool f(double d, int x)
    {
        std::cout << d;
        std::cout << x;
        return true;
    }
};

template<>
double commands::Command<CommandId::DoA>::getParam<double, 0>(const json::Doc &,
                                                              common::ParseError &)
{
    return 0.5f;
}

template<>
int commands::Command<CommandId::DoA>::getParam<int, 1>(const json::Doc &,
                                                              common::ParseError &)
{
    return 2;
}
} // namespace commands
#endif // COMMANDDOA_H
