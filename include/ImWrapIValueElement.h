#pragma once
#include "ImWrapBasicElement.h"
#include <ini.h>
#include <vector>

namespace ImWrap {
template <typename T> class IValueElement : public BasicElement {
public:
  // Constructor
  IValueElement(const std::string &label = {}) : BasicElement(label) {}

  // Destructor
  virtual ~IValueElement() override = default;

  // Is Value Element ?
  virtual bool isValueElement() const override final { return true; }

  // Set Value
  virtual void setValue(const T &value, int index) = 0;

  // Get Value
  virtual const T &value(int index) const = 0;
  inline const T &operator()(int index) const { return value(index); }

  // Get Value Count
  virtual int valueCount() const = 0;

  // Check Current Value
  virtual bool isCurrentValid() const = 0;

  // Set Current Index
  virtual void setCurrentIndex(int index) = 0;

  // Get Current Index
  virtual int currentIndex() const = 0;

  // Set Current Value
  virtual void setCurrentValue(const T &value) = 0;

  // Get Current Value
  virtual const T &currentValue() const = 0;
  inline const T &operator()() const { return currentValue(); }

  // Set Current Name
  virtual void setCurrentName(const std::string &name) {}

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
};

} // namespace ImWrap
