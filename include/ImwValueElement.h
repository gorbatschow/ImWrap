#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <class T> class ValueElement : public IValueElement<T> {
public:
  // Constructor
  ValueElement(const std::string &label = {}) : IValueElement<T>(label) {
    ValueElementImpl();
  }

  // Destructor
  virtual ~ValueElement() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index = 0) override {
    /*
      _value = std::clamp(value, _valueLimits.first, _valueLimits.second);
      */
  }

  // Get Value
  virtual const T &value(std::size_t index = 0) const override {
    return _value;
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index = 0) override {
    _valueLimits = limits;
    setValue(_value);
  }

  // Get Value Limtis
  virtual const std::pair<T, T> &
  valueLimits(std::size_t index = 0) const override {
    return _valueLimits;
  }

  // Set Value Count
  virtual void setValueCount(std::size_t) override {}

  // Get Value Count
  virtual std::size_t valueCount() const override { return 1; }

  // Set Current Index
  virtual void setCurrentIndex(std::size_t) override {}

  // Get Current Index
  virtual std::size_t currentIndex() const override { return 0; };

  // Set Current Value
  virtual void setCurrentValue(const T &value) override { setValue(value, 0); };

  // Get Current Value
  virtual const T &currentValue() const override { value(0); }
  inline const T &operator()() { return currentValue(); }

protected:
  virtual void paintElement() override {}
  inline void ValueElementImpl() {}

  T _value{};
  std::pair<T, T> _valueLimits{};
};

template <> inline void ValueElement<float>::ValueElementImpl() {
  _valueLimits = {std::numeric_limits<float>::min() / 2.0f,
                  std::numeric_limits<float>::max() / 2.0f};
}

template <> inline void ValueElement<int>::ValueElementImpl() {
  _valueLimits = {std::numeric_limits<int>::min() / 2,
                  std::numeric_limits<int>::max() / 2};
}

template <> inline void ValueElement<bool>::ValueElementImpl() {
  _valueLimits = {std::numeric_limits<bool>::min(),
                  std::numeric_limits<bool>::max()};
}

} // namespace Imw
