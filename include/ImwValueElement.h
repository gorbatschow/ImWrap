#pragma once
#include "ImwBasicElement.h"
#include <algorithm>
#include <array>

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
  std::pair<T, T> _valueLimits{std::numeric_limits<T>::min() / T(2),
                               std::numeric_limits<T>::max() / T(2)};
};

template <class T, std::size_t N>
class MultiValueElement : public IValueElement<std::array<T, N>> {
public:
  MultiValueElement(const std::string &label = {})
      : IValueElement<std::array<T, N>>(label) {}
  virtual ~MultiValueElement() override = default;

  inline void setValue(const std::array<T, N> &values) override {
    for (std::size_t i = 0; i != _values.size(); ++i) {
      setValue(i, values.at(i));
    }
  }
  inline const std::array<T, N> &value() const override final {
    return _values;
  }

  inline void setValue(std::size_t i, const T &value) {
    _values.at(i) = std::clamp(value, _valuesLimits.first.at(i),
                               _valuesLimits.second.at(i));
  }
  inline const T &value(std::size_t i) const { return _values.at(i); }

  inline void setValueLimits(std::size_t i, const std::pair<T, T> &limits) {
    _valuesLimits.first.at(i) = limits.first;
    _valuesLimits.second.at(i) = limits.second;
    setValue(i, _values.at(i));
  }
  inline const std::pair<std::array<T, N>, std::array<T, N>> &
  valueLimits() const {
    return _valuesLimits;
  }

protected:
  std::array<T, N> _values;
  std::pair<std::array<T, N>, std::array<T, N>> _valuesLimits;
};

} // namespace Imw
