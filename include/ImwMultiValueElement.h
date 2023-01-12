#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <vector>

namespace Imw {
template <typename T, bool Comparable = true>
class MultiValueElement : public IValueElement<T> {
public:
  // Constructor
  MultiValueElement(std::size_t count, const std::string &label = {})
      : IValueElement<T>(label) {
    _valueList.resize(count);
    _valueList.shrink_to_fit();
    _valueLimits.resize(count);
    _valueLimits.shrink_to_fit();
  }

  // Destructor
  virtual ~MultiValueElement() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index) override {
    if constexpr (Comparable) {
      _valueList.at(index) = std::clamp(value, _valueLimits.at(index).first,
                                        _valueLimits.at(index).second);
    } else {
      _valueList.at(index) = value;
    }
  }

  // Get Value
  virtual const T &value(std::size_t index) const override {
    return _valueList.at(index);
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index) override {
    _valueLimits.at(index) = limits;
    setValue(_valueList.at(index), index);
  }

  // Get Value Limits
  virtual const std::pair<T, T> &valueLimits(std::size_t index) const override {
    return _valueLimits.at(index);
  }

  // Set Value Count
  virtual void setValueCount(std::size_t count) override {
    _valueList.resize(count, T{});
  }

  // Get Value Count
  virtual std::size_t valueCount() const override { return _valueList.size(); }

  // Set Current Index
  virtual void setCurrentIndex(std::size_t index) override {
    _currIndex = index;
  };

  // Get Current Index
  virtual std::size_t currentIndex() const override { return _currIndex; }

  // Set Current Value
  virtual void setCurrentValue(const T &value) override {}

  // Get Current Value
  virtual const T &currentValue() const override {
    return _valueList.at(_currIndex);
  }

  // Set Value List
  void setValueList(const std::vector<T> &valueList) {
    _valueList = valueList;
    _currIndex = std::clamp<std::size_t>(_currIndex, 0, _valueList.size() - 1);
    _currIndex = _valueList.empty() ? -1 : _currIndex;
  }

protected:
  // Paint Element
  virtual void paintElement() override {}

  std::vector<T> _valueList{};
  std::vector<std::pair<T, T>> _valueLimits{};
  std::size_t _currIndex{};
};
} // namespace Imw
