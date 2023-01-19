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
    auto value{_value};
    const auto changed{ImGui::Checkbox(_label.c_str(), &value)};
    if (changed) {
      setValue(value);
      trigger();
    }
  }
};
} // namespace Imw
