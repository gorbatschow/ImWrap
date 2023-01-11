#pragma once
#include "ImwValueElement.h"

namespace Imw {
class CheckBox : public ValueElement<bool> {
public:
  // Constructor
  CheckBox(const std::string &label = {}) : ValueElement<bool>(label) {}

  // Destructor
  virtual ~CheckBox() override = default;

protected:
  // Paint Element
  virtual void paintElement() override {
    bool value{_value};
    _changed = ImGui::Checkbox(_label.c_str(), &value);
    if (_changed) {
      setValue(value);
    }
  }
};
} // namespace Imw
