#pragma once
#include "ImwBasicElement.h"

namespace Imw {
class Label : public BasicElement {
public:
  Label(const std::string &label = {}) : BasicElement(label) {}

  virtual ~Label() override = default;

protected:
  virtual void paintElement() override {
    ImGui::AlignTextToFramePadding();
    ImGui::Text("%s", _label.c_str());
  }
};
} // namespace Imw
