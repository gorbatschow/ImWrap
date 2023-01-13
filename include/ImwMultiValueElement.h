#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <vector>

namespace Imw {
template <typename T> class MultiValueElement : public IValueElement<T> {
public:
  // Constructor
  MultiValueElement(const std::string &label = {}) : IValueElement<T>(label) {}

  // Destructor
  virtual ~MultiValueElement() override = default;

  // Set Value
  virtual void setValue(const T &value, int index) override {
    _valueList.at(index) = value;
  }

  // Get Value
  virtual const T &value(int index) const override {
    return _valueList.at(index);
  }

  // Get Value Count
  virtual int valueCount() const override { return _valueList.size(); }

  // Set Current Index
  virtual void setCurrentIndex(int index) override { _currIndex = index; };

  // Get Current Index
  virtual int currentIndex() const override { return _currIndex; }

  // Set Current Value
  virtual void setCurrentValue(const T &value) override {}

  // Get Current Value
  virtual const T &currentValue() const override {
    return _valueList.at(_currIndex);
  }

  // Set Value List
  virtual void setValueList(const std::vector<T> &valueList) override {
    _valueList = valueList;
    _currIndex = std::clamp<int>(_currIndex, 0, _valueList.size() - 1);
    _currIndex = _valueList.empty() ? -1 : _currIndex;
  }

protected:
  // Paint Element
  virtual void paintElement() override {}

  std::vector<T> _valueList{};
  int _currIndex{};
};
} // namespace Imw
