#pragma once
#include "ImwBasicElement.h"

namespace Imw {
template <typename T> class IValueElement : public BasicElement {
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
  virtual void setValue(const T &value, std::size_t index) = 0;

  // Get Value
  virtual const T &value(std::size_t index) const = 0;
  inline const T &operator()(std::size_t index) { return value(index); }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index) = 0;

  // Get Value Limits
  virtual const std::pair<T, T> &valueLimits(std::size_t index = 0) const = 0;

  // Set Value Count
  virtual void setValueCount(std::size_t count) = 0;

  // Get Value Count
  virtual std::size_t valueCount() const = 0;

  // Set Current Index
  virtual void setCurrentIndex(std::size_t index) = 0;

  // Get Current Index
  virtual std::size_t currentIndex() const = 0;

  // Set Current Value
  virtual void setCurrentValue(const T &value) = 0;

  // Get Current Value
  virtual const T &currentValue() const = 0;
  inline const T &operator()() { return currentValue(); }

protected:
  // Paint Element
  virtual void paintElement() override {}

  mutable bool _changed{false};
};
} // namespace Imw
