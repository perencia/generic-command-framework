#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <tuple>


namespace common {

template<typename T>
void print(std::tuple<T> tpl)
{
    std::cout << std::get<0>(tpl) << std::endl;
}

template<typename T, typename... V>
void print(std::tuple<T, V...> tpl)
{
    std::cout << std::get<0>(tpl) << std::endl << print(std::make_tuple<V...>);
}

struct ParseError
{
    bool error = false;
};
} // namespace common

#endif // COMMON_H
