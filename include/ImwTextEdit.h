#pragma once
#include "ImwValueElement.h"
#include <misc/cpp/imgui_stdlib.h>
#include <string>

namespace Imw {
class TextEdit : public ValueElement<std::string> {
public:
  // Constructor
  TextEdit(const std::string &label = {}) : ValueElement<std::string>(label) {}

  // Destructor
  virtual ~TextEdit() override = default;

protected:
  // Paint Element
  virtual void paintElement() override {
    if (ImGui::InputText(_label.c_str(), &_value)) {
      trigger();
    }
  }
};

} // namespace Imw
