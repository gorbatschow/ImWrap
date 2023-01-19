#pragma once
#include "ImwIValueElement.h"
#include <algorithm>
#include <array>
#include <iostream>

namespace Imw {
template <typename T> class ValueElement : public IValueElement<T> {
  using Base = IValueElement<T>;

public:
  // Constructor
  ValueElement(const std::string &label = {}) : IValueElement<T>(label) {
    ValueElementImpl();
  }

  // Destructor
  virtual ~ValueElement() override = default;

  // Load State
  virtual void loadState(const mINI::INIStructure &ini) override {
    loadStateImpl(ini);
  }

  // Save State
  virtual void saveState(mINI::INIStructure &ini) override {
    saveStateImpl(ini);
  }

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
  inline void loadStateImpl(const mINI::INIStructure &ini) {}
  inline void saveStateImpl(mINI::INIStructure &ini) {}

  T _value{};
};

template <>
inline void ValueElement<int>::loadStateImpl(const mINI::INIStructure &ini) {

  const auto str = ini.get(Base::elementIdStr()).get("value");
  try {
    _value = std::stoi(str);
  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << "\n";
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }
}

template <>
inline void ValueElement<int>::saveStateImpl(mINI::INIStructure &ini) {
  ini[Base::elementIdStr()]["value"] = std::to_string(_value);
}

} // namespace Imw
