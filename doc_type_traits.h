#include "jsondoc.h"
#include "loradoc.h"

#ifndef DOC_TYPE_TRAITS_H
#define DOC_TYPE_TRAITS_H

#endif // DOC_TYPE_TRAITS_H

template <typename T> struct IdType {
  using type = void;
};

template <> struct IdType<JsonDoc> {
  using type = const char *;
};

template <> struct IdType<LoraDoc> {
  using type = char;
};

template<typename T>
using Id = typename IdType<T>::type;
