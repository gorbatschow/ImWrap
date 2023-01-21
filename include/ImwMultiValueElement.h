#pragma once
#include "ImwIValueElement.h"
#include "ImwNamedValue.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace Imw {
template <typename T> class MultiValueElement : public IValueElement<T> {
  using Base = IValueElement<T>;

public:
  // Constructor
  MultiValueElement(const std::string &label = {}) : IValueElement<T>(label) {
    MultiValueElementImpl();
  }

  // Destructor
  virtual ~MultiValueElement() override = default;

  // Load State
  virtual void loadState(const mINI::INIStructure &ini) override {
    loadStateImpl(ini);
  }

  // Save State
  virtual void saveState(mINI::INIStructure &ini) override {
    saveStateImpl(ini);
  }

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
  inline void MultiValueElementImpl() {}
  inline void loadStateImpl(const mINI::INIStructure &ini) {}
  inline void saveStateImpl(mINI::INIStructure &ini) {}

  // Default load from INI file
  void loadStateDefault(const mINI::INIStructure &ini,
                        std::function<T(std::string)> transform) {
    static const auto key_base{"value_"};
    int index{};
    for (const auto &item : ini.get(Base::elementIdStr())) {
      const auto key{item.first};
      if (key.size() < strlen(key_base) ||
          key.substr(0, strlen(key_base)) != key_base) {
        continue;
      }
      try {
        _valueList.at(index) = transform(item.second);
      } catch (const std::invalid_argument &e) {
        std::cout << "Imw::MultiValueElement<> Can't load from INI"
                  << "std::invalid_argument" << e.what() << std::endl;
      } catch (const std::out_of_range &e) {
      }
      index++;
    }
  }

  // Default save to INI file
  void saveStateDefault(mINI::INIStructure &ini) {
    static const auto key_base{"value_"};
    int index{};
    for (const auto &item : _valueList) {
      const std::string key{key_base + std::to_string(index)};
      ini[Base::elementIdStr()][key] = std::to_string(item);
      index++;
    }
  }

  std::vector<T> _valueList{};
  int _currIndex{};
};

// MultiValueElement<bool>
// -----------------------------------------------------------------------------
template <>
inline void
MultiValueElement<bool>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini,
                   [](const std::string &str) { return bool(std::stoi(str)); });
}

template <>
inline void MultiValueElement<bool>::saveStateImpl(mINI::INIStructure &ini) {
  saveStateDefault(ini);
}

// MultiValueElement<int>
// -----------------------------------------------------------------------------
template <>
inline void
MultiValueElement<int>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini, [](const std::string &str) { return std::stoi(str); });
}

template <>
inline void MultiValueElement<int>::saveStateImpl(mINI::INIStructure &ini) {
  saveStateDefault(ini);
}

// MultiValueElement<float>
// -----------------------------------------------------------------------------
template <>
inline void
MultiValueElement<float>::loadStateImpl(const mINI::INIStructure &ini) {
  loadStateDefault(ini, [](const std::string &str) { return std::stof(str); });
}

template <>
inline void MultiValueElement<float>::saveStateImpl(mINI::INIStructure &ini) {
  saveStateDefault(ini);
}

} // namespace Imw
