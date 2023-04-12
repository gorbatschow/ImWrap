#pragma once
#include "ImWrapIValueElement.h"
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>

namespace ImWrap {
template <typename T> class ValueElement : public IValueElement<T> {
  using Base = IValueElement<T>;

public:
  // Constructor
  ValueElement(const std::string &label = {}, const T &value = {})
      : IValueElement<T>(label), _value{value} {
    ValueElementImpl();
  }

  // Destructor
  virtual ~ValueElement() override = default;

  // Load State
  virtual void loadState(const mINI::INIStructure &ini) override {
    loadStateImpl(ini);
  }

  // Save State
  virtual void saveState(mINI::INIStructure &ini) const override {
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

  // Check Current Value
  virtual bool isCurrentValid() const override { return true; }

protected:
  virtual void paintElement() override {}
  inline void ValueElementImpl() {}
  inline void loadStateImpl(const mINI::INIStructure &ini) {}
  inline void saveStateImpl(mINI::INIStructure &ini) const {}

  // Default load from INI file
  void loadStateDefault(const mINI::INIStructure &ini,
                        std::function<T(std::string)> transform) {
    if (!ini.get(Base::elementIdStr()).has("value")) {
      return;
    }
    const auto str = ini.get(Base::elementIdStr()).get("value");
    try {
      setValue(transform(str));
    } catch (const std::invalid_argument &e) {
      std::cout << "Imw::ValueElement<> Can't load from INI"
                << "std::invalid_argument" << e.what() << std::endl;
    } catch (const std::out_of_range &e) {
    }
  }

  // Default save to INI file
  void saveStateDefault(mINI::INIStructure &ini) const {
    ini[Base::elementIdStr()]["value"] = std::to_string(_value);
  }

  void saveStateDefault(mINI::INIStructure &ini,
                        std::function<T(std::string)> transform) const {
    ini[Base::elementIdStr()]["value"] = transform(_value);
  }

  T _value{};
};

// ValueElement<bool>
// -----------------------------------------------------------------------------
template <>
inline void ValueElement<bool>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini,
                   [](const std::string &str) { return bool(std::stoi(str)); });
}

template <>
inline void ValueElement<bool>::saveStateImpl(mINI::INIStructure &ini) const {
  saveStateDefault(ini);
}

// ValueElement<int>
// -----------------------------------------------------------------------------
template <>
inline void ValueElement<int>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini, [](const std::string &str) { return std::stoi(str); });
}

template <>
inline void ValueElement<int>::saveStateImpl(mINI::INIStructure &ini) const {
  saveStateDefault(ini);
}

// ValueElement<float>
// -----------------------------------------------------------------------------
template <>
inline void ValueElement<float>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini, [](const std::string &str) { return std::stof(str); });
}

template <>
inline void ValueElement<float>::saveStateImpl(mINI::INIStructure &ini) const {
  saveStateDefault(ini);
}

// ValueElement<std::string>
// -----------------------------------------------------------------------------
template <>
inline void
ValueElement<std::string>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini, [](const std::string &str) { return str; });
}

template <>
inline void
ValueElement<std::string>::saveStateImpl(mINI::INIStructure &ini) const {
  saveStateDefault(ini, [](const std::string &str) { return str; });
}

} // namespace ImWrap
