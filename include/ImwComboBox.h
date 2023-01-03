#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class ComboBox : public IValueElement<T> {
public:
  ComboBox(const std::string &label = {}) : IValueElement<T>(label) {}

  ComboBox(const std::string &label,
           const std::vector<std::pair<T, std::string>> &valueList)
      : IValueElement<T>(label), _valueList(valueList) {}

  virtual ~ComboBox() override = default;

  void setValue(const T &value) override final {
    _currIndex = 0;
    for (int i = 0; i != _valueList.size(); ++i) {
      if (_valueList.at(i).first == value) {
        _currIndex = i;
        break;
      }
    }
  }

  const T &value() const override final {
    return _valueList.at(_currIndex).first;
  }

  inline void
  setValueList(const std::vector<std::pair<T, std::string>> &valueList) {
    _valueList = valueList;
    _currIndex = std::clamp<T>(_currIndex, 0, _valueList.size() - 1);
    _currIndex = _valueList.empty() ? -1 : _currIndex;
  }

  inline void setPlaceHolder(const std::string &text) { _placeholder = text; }

protected:
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
