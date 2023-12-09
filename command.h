#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "jsondoc.h"
#include "loradoc.h"


namespace waveco {
namespace detail {

template <typename T> struct Id {
  using type = void;
};

template <> struct Id<JsonDoc> {
  using type = const char *;
};

template <> struct Id<LoraDoc> {
  using type = char;
};

}

template <typename Doc> class Command {

protected:
  detail::Id<Doc>::type _id;

public:
  Command(detail::Id<Doc>::type id) {_id = id; }
  bool matches(const Doc &doc) const;
  virtual Doc run(const Doc &doc) const = 0;
};

template <> bool Command<JsonDoc>::matches(const JsonDoc &doc) const {
  return doc["id"] == _id;
}

template <> bool Command<LoraDoc>::matches(const LoraDoc &doc) const {
  std::cout << "Cmd matches " << _id << "?" << std::endl;
  return doc.id == _id;
}


} //namespace waveco

#endif // COMMAND_H
