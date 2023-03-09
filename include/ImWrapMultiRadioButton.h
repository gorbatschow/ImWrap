#pragma once
#include "ImWrapMultiValueElement.h"
#include "ImWrapNamedValue.h"

namespace ImWrap {
class MultiRadioButton : public MultiValueElement<NamedValue<int>> {
  using Base = MultiValueElement<NamedValue<int>>;

public:
  // Constructor
  MultiRadioButton(const std::string &label = {}) : Base(label) {}

  // Constructor
  MultiRadioButton(const std::vector<std::string> &radioLabels,
                   const std::string &label = {})
      : Base(label) {
    int index = 0;
    for (const auto &label : radioLabels) {
      _valueList.push_back({index++, label});
    }
  }

  // Destructor
  virtual ~MultiRadioButton() override = default;

  // Set Value List
  virtual void
  setValueList(const std::vector<NamedValue<int>> &valueList) override {
    Base::setValueList(valueList);
    int index = 0;
    for (auto &value : _valueList) {
      value.setValue(index++);
    }
  }

protected:
  virtual void paintElement() override {
    if (!_label.empty()) {
      ImGui::AlignTextToFramePadding();
      ImGui::TextUnformatted(_label.c_str());
      ImGui::SameLine(_sameLineOffset, _sameLineSpacing);
    }

    for (auto &value : _valueList) {
      if (ImGui::RadioButton(value.namePtr(), &_currIndex, value())) {
        trigger();
      }
      if (!_isVertical && value != _valueList.back()) {
        ImGui::SameLine(_sameLineOffset, _sameLineSpacing);
      }
    }
  }
};

} // namespace ImWrap
