#ifndef COMMANDS_H
#define COMMANDS_H

#include "common.h"
#include "json_parser.h"
#include <functional>
#include <iostream>
#include <tuple>

using namespace std;

namespace commands {

enum class CommandId { DoA };

template<CommandId>
class Command
{};

template<typename F>
class command_function_traits;

template<CommandId Id, typename Ret, typename... Args>
class command_function_traits<Ret (Command<Id>::*)(Args...)>
{
public:
    using args = tuple<Args...>;
};


template<CommandId Id, typename T, typename I>
class CommandRunner
{};

template<CommandId Id, typename... T, typename I, I... Is>
class CommandRunner<Id, tuple<T...>, integer_sequence<I, Is...>>
{

private:
    template <typename D, typename... J>
    D _run(Command<Id>& cmd, tuple<J...> args) const
    {
        auto f  = bind_front(&Command<Id>::f, &cmd);
        return f(get<Is>(args)...);
    }

public:
    template <typename D>
    D run(const D &d, common::ParseError& e) const
    {
        D ret;
        Command<Id> cmd;
        /* Assemble the tuple of arguments */
        auto args = make_tuple(
            [&]() -> T
            {
                T v;
                if (!e.error)
                {
                    v = cmd.template getParam<T, Is>(d, e);
                }
                return v;
            }()...);

        if(!e.error)
        {
            /* Call the command function */
          ret = _run<D>(cmd, args);
        }
        return ret;
    }
};

template<CommandId id>
auto make_command_runner()
{
    using argTypes = typename command_function_traits<
        decltype(&Command<id>::f)>::args;

    return CommandRunner<id, argTypes,
                         make_index_sequence<tuple_size<argTypes>::value>>();
}

} // namespace commands
#endif // COMMANDS_H
