#pragma once
#include "ImwBasicElement.h"
#include <vector>

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

  // Trigger
  virtual void trigger() const { _changed = true; }

  // Set Value
  virtual void setValue(const T &value, int index) = 0;

  // Get Value
  virtual const T &value(int index) const = 0;
  inline const T &operator()(int index) { return value(index); }

  // Get Value Count
  virtual int valueCount() const = 0;

  // Set Current Index
  virtual void setCurrentIndex(int index) = 0;

  // Get Current Index
  virtual int currentIndex() const = 0;

  // Set Current Value
  virtual void setCurrentValue(const T &value) = 0;

  // Get Current Value
  virtual const T &currentValue() const = 0;
  inline const T &operator()() { return currentValue(); }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits, int index){};

  // Set Value Step
  virtual void setValueStep(const T &step, int index) {}

  // Set Value Fast Step
  virtual void setValueFastStep(const T &fstep, int index) {}

  // Set Value List
  virtual void setValueList(const std::vector<T> &list) {}

protected:
  // Paint Element
  virtual void paintElement() override {}

  mutable bool _changed{false};
};
} // namespace Imw
