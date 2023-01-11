#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <class T, std::size_t N>
class MultiValueElement : public IValueElement<T> {
public:
  // Constructor
  MultiValueElement(const std::string &label = {}) : IValueElement<T>(label) {}

  // Destructor
  virtual ~MultiValueElement() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index) override {
    _value.at(index) = std::clamp(value, _valueLimits.at(index).first,
                                  _valueLimits.at(index).second);
  }

  // Get Value
  virtual const T &value(std::size_t index) const override {
    return _value.at(index);
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index) override {
    _valueLimits.at(index) = limits;
    setValue(_value.at(index), index);
  }

  // Get Value Limits
  virtual const std::pair<T, T> &valueLimits(std::size_t index) const override {
    return _valueLimits.at(index);
  }

protected:
  // Paint Element
  virtual void paintElement() override {}

  std::array<T, N> _value{};
  std::array<std::pair<T, T>, N> _valueLimits{};
};
} // namespace Imw
