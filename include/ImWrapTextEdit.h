#pragma once
#include "ImWrapValueElement.h"
#include <misc/cpp/imgui_stdlib.h>
#include <string>

namespace ImWrap {
class TextEdit : public ValueElement<std::string> {
public:
  // Constructor
  TextEdit(const std::string &label = {}, const std::string &value = {})
      : ValueElement<std::string>(label, value) {}

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

} // namespace ImWrap
