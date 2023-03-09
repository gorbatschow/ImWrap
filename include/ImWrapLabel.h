#pragma once
#include "ImWrapBasicElement.h"

namespace ImWrap {
class Label : public BasicElement {
public:
  // Constructor
  Label(const std::string &label = {}) : BasicElement(label) {}

  // Destructor
  virtual ~Label() override = default;

protected:
  // Paint Element
  virtual void paintElement() override {
    ImGui::AlignTextToFramePadding();
    ImGui::Text("%s", _label.c_str());
  }
};
} // namespace ImWrap
