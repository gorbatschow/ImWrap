#pragma once
#include "ImwMultiValueElement.h"
#include "ImwNamedValue.h"

namespace Imw {
class MultiRadioButton : public MultiValueElement<NamedValue<int>> {
  using Base = MultiValueElement<NamedValue<int>>;

public:
  // Constructor
  MultiRadioButton(std::size_t count, const std::string &label = {})
      : Base(count, label) {
    int index = 0;
    for (auto &value : _valueList) {
      value.setName("Combo_" + std::to_string(index));
      value.setValue(index++);
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

  // Get Value
  inline const int &operator()() { return Base::currentValue().value(); }

protected:
  virtual void paintElement() override {
    for (auto &value : _valueList) {
      if (ImGui::RadioButton(value.namePtr(), &_currIndex, value())) {
        _changed = true;
      }
    }
  }
};

} // namespace Imw
