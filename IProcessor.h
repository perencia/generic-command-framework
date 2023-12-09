#ifndef IPROCESSOR_H
#define IPROCESSOR_H

template <typename Doc> class IProcessor {
public:
  virtual Doc process(const char* data) const = 0;
  virtual ~IProcessor() = default;
};

#endif // IPROCESSOR_H
