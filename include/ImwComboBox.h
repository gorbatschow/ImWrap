#pragma once
#include "ImwIValueElement.h"
#include <vector>

namespace Imw {
template <class T> class ComboBox : public IValueElement<T> {
public:
  // Constructor
  ComboBox(const std::string &label = {}) : IValueElement<T>(label) {}

  // Constructor
  ComboBox(const std::string &label,
           const std::vector<std::pair<T, std::string>> &valueList)
      : IValueElement<T>(label), _valueList(valueList) {}

  // Destructor
  virtual ~ComboBox() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index = 0) override {
    _currIndex = valueIndex(value);
  }

  // Get Value
  virtual const T &value(std::size_t) const override {
    assert(_currIndex >= 0);
    return _valueList.at(_currIndex).first;
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &,
                              std::size_t index = 0) override {}

  // Get Value Limits
  virtual const std::pair<T, T> &valueLimits(std::size_t) const override {
    static const std::pair<T, T> limits{};
    return limits;
  }

  // Get Value Count
  virtual std::size_t valueCount() const override { return _valueList.size(); }

  // Get Value Index
  inline int valueIndex(const T &value) const {
    for (int i = 0; i != _valueList.size(); ++i) {
      if (_valueList.at(i).first == value) {
        return i;
      }
    }
    return -1;
  }

  // Set Value List
  inline void
  setValueList(const std::vector<std::pair<T, std::string>> &valueList) {
    _valueList = valueList;
    _currIndex = std::clamp<T>(_currIndex, 0, _valueList.size() - 1);
    _currIndex = _valueList.empty() ? -1 : _currIndex;
  }

  // Set Place Holder
  inline void setPlaceHolder(const std::string &text) { _placeholder = text; }

protected:
  // Paint Element
  virtual void paintElement() override {
    _currIndex = _valueList.empty() ? -1 : _currIndex;
    if (_currIndex < 0) {
      // Value list IS empty
      if (ImGui::BeginCombo(IValueElement<T>::_label.c_str(),
                            _placeholder.c_str())) {
        ImGui::EndCombo();
      }
    } else {
      // Value list is NOT empty
      if (ImGui::BeginCombo(IValueElement<T>::_label.c_str(),
                            _valueList.at(_currIndex).second.c_str())) {
        for (size_t i = 0; i != _valueList.size(); ++i) {
          if (ImGui::Selectable(_valueList[i].second.c_str(),
                                i == _currIndex)) {
            _currIndex = i;
            IValueElement<T>::_changed = true;
          }
        }
        ImGui::EndCombo();
      }
    }
  }

  std::vector<std::pair<T, std::string>> _valueList;
  int _currIndex{0};
  std::string _placeholder{};
};
} // namespace Imw
