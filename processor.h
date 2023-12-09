#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "IProcessor.h"
#include "loradoc.h"
#include "jsondoc.h"
#include <array>


namespace waveco {

namespace detail {
template <typename Doc> bool deserialize(Doc&, const char*);

template <> bool deserialize(JsonDoc& d, const char* data) {
  return deserializeJson(d, data) == DeserializationError::Ok;
}

template <> bool deserialize(LoraDoc& d, const char* data) {
  d.id = data[0];
  return true;
}
} // namespace detail


template <typename Doc, typename CmdContainer> class Processor: public IProcessor<Doc> {

private:
  CmdContainer& _cmds;

public:
  Processor(CmdContainer& cmds) : _cmds(cmds){}
  Doc process(const char* data) const;
};

template <typename Doc, typename CmdContainer>  Doc Processor<Doc, CmdContainer>::process(const char* data) const {
  Doc response, request;
  if (detail::deserialize<Doc>(request, data)) {
    auto cmd = _cmds.get(request);
    response = cmd->run(request);
  }
  return response;
}



} // namespace waveco

#endif // PROCESSOR_H
