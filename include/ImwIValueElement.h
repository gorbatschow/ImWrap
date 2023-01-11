#pragma once
#include "ImwBasicElement.h"

namespace Imw {
template <class T> class IValueElement : public BasicElement {
public:
  // Constructor
  IValueElement(const std::string &label = {}) : BasicElement(label) {}

  // Destructor
  virtual ~IValueElement() override = default;

  // Handle
  virtual bool handle() const {
    const auto changed{_changed};
    _changed = false;
    return changed;
  }

  // Set Value
  virtual void setValue(const T &value, std::size_t index = 0) = 0;

  // Get Value
  virtual const T &value(std::size_t index = 0) const = 0;
  inline const T &operator()(std::size_t index = 0) { return value(index); }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index = 0) = 0;

  // Get Value Limits
  virtual const std::pair<T, T> &valueLimits(std::size_t index = 0) const = 0;

protected:
  // Paint Element
  virtual void paintElement() override {}

  mutable bool _changed{false};
};
} // namespace Imw
