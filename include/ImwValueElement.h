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
  virtual void setValue(const T &value, std::size_t index = 0) override {
    _value = value;
  }

  // Get Value
  virtual const T &value(std::size_t index = 0) const override {
    return _value;
  }

  // Get Value Count
  virtual std::size_t valueCount() const override { return 1; }

  // Set Current Index
  virtual void setCurrentIndex(std::size_t) override {}

  // Get Current Index
  virtual std::size_t currentIndex() const override { return 0; };

  // Set Current Value
  virtual void setCurrentValue(const T &value) override { setValue(value, 0); };

  // Get Current Value
  virtual const T &currentValue() const override { return value(); }
  inline const T &operator()() { return currentValue(); }

protected:
  virtual void paintElement() override {}
  inline void ValueElementImpl() {}

  T _value{};
};

} // namespace Imw
