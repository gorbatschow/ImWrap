#pragma once
#include "ImwValueElement.h"

namespace Imw {
class CheckBox : public ValueElement<bool> {
public:
  CheckBox(const std::string &label = {}) : ValueElement<bool>(label) {}

  virtual ~CheckBox() override = default;

protected:
  virtual void paintElement() override {
    bool value{_value};
    _changed = ImGui::Checkbox(_label.c_str(), &value);
    if (_changed) {
      setValue(value);
    }
  }
};
} // namespace Imw
