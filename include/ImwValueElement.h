#pragma once
#include "ImwBasicElement.h"
#include <algorithm>

namespace Imw {
template <class T> class IValueElement : public BasicElement {
public:
  IValueElement(const std::string &label = {}) : BasicElement(label) {}

  virtual ~IValueElement() override = default;

  virtual bool handle() const {
    const auto changed{_changed};
    _changed = false;
    return changed;
  }

  virtual void setValue(const T &value) = 0;
  virtual const T &value() const = 0;
  inline const T &operator()() { return value(); }

protected:
  mutable bool _changed{false};
};

template <class T> class ValueElement : public IValueElement<T> {
public:
  ValueElement(const std::string &label = {}) : IValueElement<T>(label) {}

  virtual ~ValueElement() override = default;

  inline void setValue(const T &value) override {
    _value = std::clamp(value, _valueLimits.first, _valueLimits.second);
  }
  inline const T &value() const override final { return _value; }

  inline void setValueLimits(const std::pair<T, T> &limits) {
    _valueLimits = limits;
    setValue(_value);
  }
  inline const std::pair<T, T> &valueLimits() const { return _valueLimits; }

protected:
  T _value{};
  std::pair<T, T> _valueLimits{std::numeric_limits<T>::min(),
                               std::numeric_limits<T>::max()};
};
} // namespace Imw
