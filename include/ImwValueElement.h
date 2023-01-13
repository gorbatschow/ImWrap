#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <typename T> class ValueElement : public IValueElement<T> {
public:
  // Constructor
  ValueElement(const std::string &label = {}) : IValueElement<T>(label) {
    ValueElementImpl();
  }

  // Destructor
  virtual ~ValueElement() override = default;

  // Set Value
  virtual void setValue(const T &value, int index = 0) override {
    _value = value;
  }

  // Get Value
  virtual const T &value(int index = 0) const override { return _value; }

  // Get Value Count
  virtual int valueCount() const override { return 1; }

  // Set Current Index
  virtual void setCurrentIndex(int index) override {}

  // Get Current Index
  virtual int currentIndex() const override { return 0; };

  // Set Current Value
  virtual void setCurrentValue(const T &value) override { setValue(value, 0); };

  // Get Current Value
  virtual const T &currentValue() const override { return value(); }

protected:
  virtual void paintElement() override {}
  inline void ValueElementImpl() {}

  T _value{};
};

} // namespace Imw
